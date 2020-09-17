#pragma once

#include "dispatcher.hpp"
#include "message_queue.hpp"

#include <functional>
#include <memory>

namespace message {
using DispatcherType = Dispatcher;
using MsgType = MessageBase;
using Handle = std::function<void(MsgType)>;

// template <typename DispatcherType, typename MsgType, typename Handle>
class TemplateDispatcher {
public:
  TemplateDispatcher(TemplateDispatcher&& rhs) noexcept
    : queue_{std::move(rhs.queue_)}, previous_dispatcher_(rhs.previous_dispatcher_), chained_(rhs.chained_) {
    rhs.chained_ = true;
  }

  TemplateDispatcher(const TemplateDispatcher& rhs) = delete;
  auto operator=(const TemplateDispatcher& rhs) -> TemplateDispatcher& = delete;

private:
  void run() {
    while (true) {
      if (auto queue = queue_.lock()) {
        auto msg = queue->Pop();
      }
    }
  }

  auto dispatch(const std::shared_ptr<MessageBase>& msg_base) -> bool {
    if (auto* msg = dynamic_cast<WrappedMessage<MsgType>*>(msg_base.get())) {
      handler_(msg->contents_);
      return true;
    }

    return previous_dispatcher_->dispatch(msg_base);
  }

private:
  std::weak_ptr<Queue> queue_;
  DispatcherType* previous_dispatcher_ = nullptr;
  Handle handler_;
  bool chained_ = false;
};
} // namespace message