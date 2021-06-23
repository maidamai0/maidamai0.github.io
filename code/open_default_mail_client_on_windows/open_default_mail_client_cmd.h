#pragma once

/**
 * @file open_default_mail_client_cmd.h
 * @author tonghao.yuan (tonghao.yuan@csdental.com)
 * @brief Open default mail client
 *
 * 1. get the default mail client from registry
 * 2. if outlook, send with outlook specific method
 * 3. if not, send with mailto method.
 * @version 0.1
 * @date 2020-02-11
 *
 * @copyright Copyright (c) 2020 Carestream Dental,LLC. All Rights Reserved
 *
 */

#include <string>

class OpenDefaultMailClientCmd final {
public:
  OpenDefaultMailClientCmd(std::string&& receiver) noexcept;
  void SetSubject(std::string&& subject) noexcept;
  void SetBody(std::string&& body) noexcept;
  void Run();

  [[nodiscard]] auto GetMailName() const noexcept -> std::string;
  [[nodiscard]] auto GetMailPath() const noexcept -> std::string;

private:
  void get_default_mail_client() noexcept;
  [[nodiscard]] auto get_mail_path_reg_key() const noexcept -> std::string;
  void send_with_mailto_protocol() noexcept;
  void send_with_outlook() noexcept;
  [[nodiscard]] auto get_animation_path() const noexcept -> std::string;

  enum class MAIL_CLIENT { k_outlook, k_others };

private:
  std::string receiver_;
  std::string subject_;
  std::string body_;

  std::string mail_path_;
  std::string mail_name_;

  MAIL_CLIENT mail_type_ = MAIL_CLIENT::k_others;
};
