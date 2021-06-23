#include "open_default_mail_client_cmd.h"

#include <filesystem>
#include <iostream>
#include <string>

namespace {
constexpr auto reg_key_mail = R"(HKEY_LOCAL_MACHINE\SOFTWARE\Clients\Mail)";
constexpr auto reg_key_default_value = R"(Default)";
constexpr auto reg_key_mail_command = R"(shell\open\command)";

constexpr auto mail_name_outlook{"Outlook"};
} // namespace

OpenDefaultMailClientCmd::OpenDefaultMailClientCmd(std::string&& receiver) noexcept : receiver_(std::move(receiver)) {
  get_default_mail_client();
}

void OpenDefaultMailClientCmd::SetSubject(std::string&& subject) noexcept {
  subject_ = std::move(subject);
}

void OpenDefaultMailClientCmd::SetBody(std::string&& body) noexcept {
  body_ = std::move(body);
}

auto OpenDefaultMailClientCmd::GetMailName() const noexcept -> std::string {
  return mail_name_;
}

auto OpenDefaultMailClientCmd::GetMailPath() const noexcept -> std::string {
  return mail_path_;
}

void OpenDefaultMailClientCmd::get_default_mail_client() noexcept {
  // read registry
  // mail_name_ = QSettings(reg_key_mail, QSettings::NativeFormat).value(reg_key_default_value).toString();
  if (mail_name_.empty()) {
    std::cout << "No default email client found";
    return;
  }
  if (mail_name_.find(mail_name_outlook) != std::string::npos) {
    mail_type_ = MAIL_CLIENT::k_outlook;
  }

  // read registry
  // mail_path_ = QSettings(get_mail_path_reg_key(), QSettings::NativeFormat).value(reg_key_default_value).toString();
  if (mail_path_.empty()) {
    std::cout << "mail " << mail_name_ << " is not valid";
    return;
  }

  std::cout << "Mail path is " << mail_path_;
}

std::string OpenDefaultMailClientCmd::get_mail_path_reg_key() const noexcept {
  // return registry key
  // return reg_key_mail + QDir::separator() + mail_name_ + QDir::separator() + reg_key_mail_command;
  return {};
}

void OpenDefaultMailClientCmd::Run() {
  switch (mail_type_) {
    case MAIL_CLIENT::k_outlook:
      send_with_outlook();
      break;
    default:
      send_with_mailto_protocol();
      break;
  }
}

void OpenDefaultMailClientCmd::send_with_outlook() noexcept {
  std::string exe = mail_path_;

  // remove option
  // const auto index = exe.indexOf("/");
  // if (index != -1) {
  // exe.truncate(index);

  // QProcess mail_client;
  // mail_client.setProgram(exe);

  // OUTLOOK -c ipm.note -m
  // "example.mail@com&cc=other@mail.com&subject=impression video&body=from
  // csdental" -a "filename"
  // QStringList args;
  // std::string msg{receiver_ + "&subject=" + subject_};

  // if (!body_.empty()) {
  //   msg = msg + "&body=" + body_;
  // }

  // args << "-recycle"
  //      << "-c"
  //      << "ipm.note"
  //      << "-m" << msg << "-a" << get_animation_path();
  // mail_client.setArguments(args);

  // std::string ss;
  // for (auto& s : args) {
  //   ss += s;
  // }

  // std::cout << "outlook arguments is " << ss;

  // mail_client.startDetached();
}

void OpenDefaultMailClientCmd::send_with_mailto_protocol() noexcept {
  std::string mailto_url{std::string("mailto:") + receiver_ + "?subject=" + subject_ + "&body=" + body_};
  // QDesktopServices::openUrl(mailto_url);
  // open url
}

auto OpenDefaultMailClientCmd::get_animation_path() const noexcept -> std::string {
  // TODO complete this
  return R"(C:\Windows\System32\mapi32.dll)";
}
