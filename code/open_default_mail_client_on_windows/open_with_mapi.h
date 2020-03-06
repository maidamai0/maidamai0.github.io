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
#include <string>
#include <vector>
#include <tuple>

#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include "MAPI.h"

class MapiClient {
public:
  MapiClient() = default;
  ~MapiClient();

  /**
   * @brief Send Mail
   *
   * @return int  0 for success, others for error.
   */
  int SendMail();

  /**
   * @brief Add four types of recipients
   * @{
   */
  void AddTo(std::wstring&& address, std::wstring&& name) noexcept;
  void AddCC(std::wstring&& address, std::wstring&& name) noexcept;
  void AddBCC(std::wstring&& address, std::wstring&& name) noexcept;
  void AddOriginator(std::wstring&& address, std::wstring&& name) noexcept;
  /**
   * @}
   *
   */

  /**
   * @brief add attachemnt
   *
   * @param file  full path of the file
   */
  void AddAtachment(std::wstring&& file) noexcept;

  void SetSubject(std::wstring&& subject) noexcept;
  void SetBody(std::wstring&& body) noexcept;

private:
  bool load_mapi_dll();
  void add_recipients(const int type, std::wstring&& address,
                      std::wstring&& name) noexcept;

private:
  std::vector<std::wstring> files_;
  // type, address, name
  std::vector<std::tuple<int, std::wstring, std::wstring>> recipients_;
  std::wstring subject_;
  std::wstring body_;
};