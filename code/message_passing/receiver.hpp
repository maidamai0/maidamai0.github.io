#pragma once

#include "message_queue.hpp"
#include "sender.hpp"

#include <memory>

namespace message {

class Receiver {
  auto GetSender() -> Sender {
    return Sender(queue_);
  }

private:
  std::shared_ptr<Queue> queue_;
};

} // namespace message