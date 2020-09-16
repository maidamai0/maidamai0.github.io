#pragma once

#include <memory>
#include <mutex>
#include <queue>
#include <string>

namespace message {

struct MessageBase {
  virtual ~MessageBase();
};

template <typename MsgType>
struct WrappedMessage final : public MessageBase {
  MsgType contents_;
  explicit WrappedMessage(const MsgType& contents) : contents_{contents} {
  }
};

class Queue final {
public:
  template <typename MsgType>
  void Push(const MsgType& msg) {
    std::lock_guard<std::mutex> lock(mtx_);
    messages_.push(std::make_shared<MessageBase>(msg));
    cv_.notify_all();
  }

  auto Pop() -> std::shared_ptr<MessageBase> {
    std::unique_lock<std::mutex> lock(mtx_);
    cv_.wait(lock, [this]() { return !messages_.empty(); });
    auto msg = messages_.back();
    messages_.pop();
    return msg;
  }

private:
  std::mutex mtx_;
  std::condition_variable cv_;
  std::queue<std::shared_ptr<MessageBase>> messages_;
};

} // namespace message