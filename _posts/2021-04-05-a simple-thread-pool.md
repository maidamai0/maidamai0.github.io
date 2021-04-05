---
layout: post
---

A simple thread pool based on, highly inspired by [Easy3D](https://github.com/LiangliangNan/Easy3D/blob/main/test/ThreadPool/ThreadPool.h)

# Implement a simple thread pool

This thread pool is a consumer/producer queue without the consume API. Users produce `task` with `Push` API, which will be consumed by the threads(workers) of the pool.

The code is as follows:

```cpp
#include <atomic>
#include <cassert>
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

class ThreadPool {
  using task_type = std::function<void()>;

public:
  ThreadPool(size_t num = std::thread::hardware_concurrency()) {
    for (size_t i = 0; i < num; ++i) {
      workers_.emplace_back(std::thread([this] {
        while (true) {
          task_type task;
          {
            std::unique_lock<std::mutex> lock(task_mutex_);
            task_cond_.wait(lock, [this] { return !tasks_.empty(); });
            task = std::move(tasks_.front());
            tasks_.pop();
          }
          if (!task) {
            std::cout << "worker #" << std::this_thread::get_id() << " exited" << std::endl;
            push_stop_task();
            return;
          }
          task();
        }
      }));
      std::cout << "worker #" << workers_.back().get_id() << " started" << std::endl;
    }
  }

  ~ThreadPool() {
    Stop();
  }

  void Stop() {
    push_stop_task();
    for (auto& worker : workers_) {
      if (worker.joinable()) {
        worker.join();
      }
    }

    // clear all pending tasks
    std::queue<task_type> empty{};
    std::swap(tasks_, empty);
  }

  template <typename F, typename... Args>
  auto Push(F&& f, Args&&... args) {
    using return_type = std::invoke_result_t<F, Args...>;
    auto task
      = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    auto res = task->get_future();

    {
      std::lock_guard<std::mutex> lock(task_mutex_);
      tasks_.emplace([task] { (*task)(); });
    }
    task_cond_.notify_one();

    return res;
  }

private:
  void push_stop_task() {
    std::lock_guard<std::mutex> lock(task_mutex_);
    tasks_.push(task_type{});
    task_cond_.notify_one();
  }

  std::vector<std::thread> workers_;
  std::queue<task_type> tasks_;
  std::mutex task_mutex_;
  std::condition_variable task_cond_;
};
```

## wrap the task and support arbitrary return type and arguments

We have to wrap all the functions users provide to one type before we can put the task into the queue.
So the key here is how to wrap arbitrary tasks which may have different return type and arguments.

here are the steps:

1. use `std::invoke_result_t` to get the return type
2. use std::bind to erase argument types
3. use lambda to erase the return type

## How can use get the return value

Use `std::future` returned by `Push`
