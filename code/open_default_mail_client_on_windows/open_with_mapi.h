#pragma once

/**
 * @file open_with_mapi.h
 * @author tonghao.yuan (tonghao.yuan@csdental.com)
 * @brief Open with mapi interface
 * @version 0.1
 * @date 2020-02-21
 *
 * @copyright Copyright (c) 2020 Carestream Dental,LLC. All Rights Reserved
 *
 */

#include <atomic>
#include <memory>

// clang-format off
#include <Windows.h>
#include <string>
#include <vector>
#include "MAPI.h"
// clang-format on

class MapiClient {
public:
  MapiClient();
  ~MapiClient();
  inline bool IsValid() const noexcept;
  void SendMail();

private:
  void load_mapi_dll();
  void construct_message();

private:
  std::atomic_bool is_valid_{false};

  lpMapiMessageW message_;
  std::vector<std::string> attatchments_;
  std::string subject_;
  std::string body_;
  std::string reveiver_;
};