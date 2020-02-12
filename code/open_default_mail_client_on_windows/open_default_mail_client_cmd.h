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

#include <QString>
#include <string>

class OpenDefaultMailClientCmd final {
public:
  OpenDefaultMailClientCmd(QString&& receiver) noexcept;
  void SetSubject(QString&& subject) noexcept;
  void SetBody(QString&& body) noexcept;
  void Run();

  std::string GetMailName() const noexcept;
  std::string GetMailPath() const noexcept;

private:
  void get_default_mail_client() noexcept;
  QString get_mail_path_reg_key() const noexcept;
  void send_with_mailto_protocol() noexcept;
  void send_with_outlook() noexcept;
  QString get_animation_path() const noexcept;

private:
  enum class MAIL_CLIENT { k_outlook, k_others };

private:
  QString receiver_;
  QString subject_;
  QString body_;

  QString mail_path_;
  QString mail_name_;

  MAIL_CLIENT mail_type_ = MAIL_CLIENT::k_others;
};
