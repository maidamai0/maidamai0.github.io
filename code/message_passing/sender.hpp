#pragma once

#include "message_queue.hpp"
#include <cassert>
#include <memory>
#include <type_traits>

namespace message {
class Sender final {
public:
  Sender() = default;

  explicit Sender(std::weak_ptr<Queue>&& queue) : queue_{std::move(queue)} {
  }

  template <typename MsgType>
  void Send(MsgType& msg) {
    assert(queue_ && "queue is nullptr");
    queue_->Push(msg);
  }

private:
  std::weak_ptr<Queue> queue_;
};
} // namespace message