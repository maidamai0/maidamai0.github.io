#pragma once

#include <memory>
#include <type_traits>

#include "message_queue.hpp"

namespace message {

class CloseQueue {};

class Dispatcher {
  // template <typename Dispatcher, typename MsgType, typename Handle>
  // friend class TemplateDispatcher;

public:
  Dispatcher(const Dispatcher&) = delete;
  auto operator=(const Dispatcher& rhs) -> Dispatcher& = delete;

  Dispatcher(Dispatcher&& rhs) noexcept : queue_{std::move(rhs.queue_)}, chained_(rhs.chained_) {
    rhs.chained_ = true;
  }

  explicit Dispatcher(std::shared_ptr<Queue>& queue) : queue_(queue) {
  }

  ~Dispatcher() {
    if (!chained_) {
      run();
    }
  }

private:
  auto dispatch(const std::shared_ptr<MessageBase>& msg) {
    if (dynamic_cast<WrappedMessage<CloseQueue>*>(msg.get()) != nullptr) {
      throw CloseQueue();
    }

    return false;
  }

  void run() {
    while (true) {
      if (auto queue = queue_.lock()) {
        auto msg = queue->Pop();
        dispatch(msg);
      } // check weak_ptr
    }   // work loop
  }

private:
  std::weak_ptr<Queue> queue_;
  bool chained_ = false;
};

} // namespace message