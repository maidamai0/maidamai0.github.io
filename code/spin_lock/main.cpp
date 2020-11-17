#include <array>
#include <atomic>
#include <mutex>
#include <thread>

#include "doctest/doctest.h"

constexpr auto worker_num = 20;

/**
 * @brief simple spin lock meets BasicLockable(https://en.cppreference.com/w/cpp/named_req/BasicLockable)
 *
 */
class SpinLock final {
public:
  SpinLock() = default;
  ~SpinLock() = default;

  void lock() {
    while (lock_.test_and_set()) {
      std::this_thread::yield(); // speed up test
      // spin
    }
  }
  void unlock() {
    lock_.clear();
  }

  SpinLock(const SpinLock&) = delete;
  SpinLock& operator=(const SpinLock&) = delete;

private:
  std::atomic_flag lock_ = ATOMIC_FLAG_INIT;
};

TEST_CASE("no lock") {
  auto sum = 0;
  std::vector<std::thread> workers;

  workers.reserve(worker_num);
  for (auto i = 0; i < worker_num; ++i) {
    workers.emplace_back(std::thread([&sum] {
      for (auto cnt = 0; cnt < worker_num; ++cnt) {
        using namespace std::chrono_literals;
        ++sum;
        std::this_thread::sleep_for(1us);
      }
    }));
  }

  for (auto& worker : workers) {
    worker.join();
  }

  CHECK(sum == worker_num * worker_num);
}

TEST_CASE("spin lock") {
  auto sum = 0;
  std::vector<std::thread> workers;
  SpinLock lock;

  workers.reserve(worker_num);
  for (auto i = 0; i < worker_num; ++i) {
    workers.emplace_back(std::thread([&sum, &lock] {
      for (auto cnt = 0; cnt < worker_num; ++cnt) {
        std::lock_guard<SpinLock> guard(lock);
        using namespace std::chrono_literals;
        ++sum;
        std::this_thread::sleep_for(1us);
      }
    }));
  }

  for (auto& worker : workers) {
    worker.join();
  }

  CHECK(sum == worker_num * worker_num);
}
