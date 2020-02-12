#include "open_default_mail_client_cmd.h"

#include <QDebug>
#include <QDesktopServices>
#include <QDir>
#include <QProcess>
#include <QSettings>
#include <QUrl>

namespace {
const QString reg_key_mail = R"(HKEY_LOCAL_MACHINE\SOFTWARE\Clients\Mail)";
const QString reg_key_default_value = R"(Default)";
const QString reg_key_mail_command = R"(shell\open\command)";

const QString mail_name_outlook{"Outlook"};
} // namespace

OpenDefaultMailClientCmd::OpenDefaultMailClientCmd(QString&& receiver) noexcept
  : receiver_(std::move(receiver)) {
  get_default_mail_client();
}

void OpenDefaultMailClientCmd::SetSubject(QString&& subject) noexcept {
  subject_ = std::move(subject);
}

void OpenDefaultMailClientCmd::SetBody(QString&& body) noexcept {
  body_ = std::move(body);
}

auto OpenDefaultMailClientCmd::GetMailName() const noexcept -> std::string {
  return mail_name_.toStdString();
}

auto OpenDefaultMailClientCmd::GetMailPath() const noexcept -> std::string {
  return mail_path_.toStdString();
}

void OpenDefaultMailClientCmd::get_default_mail_client() noexcept {
  mail_name_ = QSettings(reg_key_mail, QSettings::NativeFormat)
                 .value(reg_key_default_value)
                 .toString();
  if (mail_name_.isEmpty()) {
    qDebug() << "No default email client found";
    return;
  }
  if (mail_name_.contains(mail_name_outlook)) {
    mail_type_ = MAIL_CLIENT::k_outlook;
  }

  mail_path_ = QSettings(get_mail_path_reg_key(), QSettings::NativeFormat)
                 .value(reg_key_default_value)
                 .toString();
  if (mail_path_.isEmpty()) {
    qDebug() << "mail " << mail_name_ << " is not valid";
    return;
  }

  qDebug() << "Mail path is " << mail_path_;
}

QString OpenDefaultMailClientCmd::get_mail_path_reg_key() const noexcept {
  return reg_key_mail + QDir::separator() + mail_name_ + QDir::separator()
         + reg_key_mail_command;
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
  QString exe = mail_path_;

  // remove option
  const auto index = exe.indexOf("/");
  if (index != -1) {
    exe.truncate(index);
  }

  QProcess mail_client;
  mail_client.setProgram(exe);

  // OUTLOOK -c ipm.note -m
  // "example.mail@com&cc=other@mail.com&subject=impression video&body=from
  // csdental" -a "filename"
  QStringList args;
  QString msg{receiver_ + "&subject=" + subject_};

  if (!body_.isEmpty()) {
    msg = msg + "&body=" + body_;
  }

  args << "-recycle"
       << "-c"
       << "ipm.note"
       << "-m" << msg << "-a" << get_animation_path();
  mail_client.setArguments(args);

  QString ss;
  for (auto& s : args) {
    ss += s;
  }

  qDebug() << "outlook arguments is " << ss;

  mail_client.startDetached();
}

void OpenDefaultMailClientCmd::send_with_mailto_protocol() noexcept {
  QString mailto_url{QString("mailto:") + receiver_ + "?subject=" + subject_
                     + "&body=" + body_};
  QDesktopServices::openUrl(mailto_url);
}

QString OpenDefaultMailClientCmd::get_animation_path() const noexcept {
  // TODO complete this
  return R"(C:\Windows\System32\mapi32.dll)";
}
