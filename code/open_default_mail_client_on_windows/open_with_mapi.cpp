
#include "open_with_mapi.h"

#include <memory>
#include <string>
#include <iostream>
#include <limits>
#include <cassert>

namespace {
const std::string mapi_dll_name{"mapi32.dll"};
HMODULE mapi32dll = nullptr;
LPMAPISENDMAILW MAPISendMailWPtr = nullptr;

// copy from MAPI.h
const std::string err_string[]{"MAPI SUCCESS", // 0
                               "MAPI_USER_ABORT",
                               "MAPI_E_FAILURE",
                               "MAPI_E_LOGON_FAILURE",
                               "MAPI_E_DISK_FULL",
                               "MAPI_E_INSUFFICIENT_MEMORY", // 5
                               "MAPI_E_ACCESS_DENIED",
                               "INVALID",
                               "MAPI_E_TOO_MANY_SESSIONS",
                               "MAPI_E_TOO_MANY_FILES",
                               "MAPI_E_TOO_MANY_RECIPIENTS", // 10
                               "MAPI_E_ATTACHMENT_NOT_FOUND",
                               "MAPI_E_ATTACHMENT_OPEN_FAILURE",
                               "MAPI_E_ATTACHMENT_WRITE_FAILURE",
                               "MAPI_E_UNKNOWN_RECIPIENT",
                               "MAPI_E_BAD_RECIPTYPE", // 15
                               "MAPI_E_NO_MESSAGES",
                               "MAPI_E_INVALID_MESSAGE",
                               "MAPI_E_TEXT_TOO_LARGE",
                               "MAPI_E_INVALID_SESSION",
                               "MAPI_E_TYPE_NOT_SUPPORTED", // 20
                               "MAPI_E_AMBIGUOUS_RECIPIENT",
                               "MAPI_E_MESSAGE_IN_USE",
                               "MAPI_E_NETWORK_FAILURE",
                               "MAPI_E_INVALID_EDITFIELDS",
                               "MAPI_E_INVALID_RECIPS", // 25
                               "MAPI_E_NOT_SUPPORTED",
                               "MAPI_E_UNICODE_NOT_SUPPORTED",
                               "MAPI_E_ATTACHMENT_TOO_LARGE"};

} // namespace

MapiClient::~MapiClient() {
  if (mapi32dll != nullptr) {
    FreeLibrary(mapi32dll);
    mapi32dll = nullptr;
  }
}

auto MapiClient::load_mapi_dll() -> bool {
  // load dll
  mapi32dll = LoadLibrary(mapi_dll_name.c_str());
  if (mapi32dll == nullptr) {
    std::cerr << "Load " << mapi_dll_name << "failed" << std::endl;
    return false;
  }

  // get functin address
  MAPISendMailWPtr = reinterpret_cast<LPMAPISENDMAILW>(
    GetProcAddress(mapi32dll, "MAPISendMailW"));
  if (MAPISendMailWPtr == nullptr) {
    std::cerr << "Get MAPISendMailW failed" << std::endl;
    // dll will be freed in destructor
    return false;
  }

  return true;
}

void MapiClient::AddTo(std::wstring&& address, std::wstring&& name) noexcept {
  add_recipients(MAPI_TO, std::move(address), std::move(name));
}

void MapiClient::AddCC(std::wstring&& address, std::wstring&& name) noexcept {
  add_recipients(MAPI_CC, std::move(address), std::move(name));
}

void MapiClient::AddBCC(std::wstring&& address, std::wstring&& name) noexcept {
  add_recipients(MAPI_BCC, std::move(address), std::move(name));
}

void MapiClient::AddOriginator(std::wstring&& address,
                               std::wstring&& name) noexcept {
  add_recipients(MAPI_ORIG, std::move(address), std::move(name));
}

void MapiClient::add_recipients(const int type, std::wstring&& address,
                                std::wstring&& name) noexcept {
  assert(!address.empty() || !name.empty());
  recipients_.emplace_back(type, std::move(address), std::move(name));
}

void MapiClient::AddAtachment(std::wstring&& file) noexcept {
  files_.emplace_back(std::move(file));
}

void MapiClient::SetSubject(std::wstring&& subject) noexcept {
  subject_ = std::move(subject);
}

void MapiClient::SetBody(std::wstring&& body) noexcept {
  body_ = std::move(body);
}

auto MapiClient::SendMail() -> int {
  if (!load_mapi_dll()) {
    return -1;
  }

  auto message_ = new MapiMessageW();
  message_->lpszSubject = const_cast<PWSTR>(subject_.c_str());
  message_->lpszNoteText = const_cast<PWSTR>(body_.c_str());

  // recipients
  std::vector<MapiRecipDescW> recipients;
  for (const auto& tuple : recipients_) {
    MapiRecipDescW recip;
    ZeroMemory(&recip, sizeof(MapiRecipDescW));
    recip.ulRecipClass = std::get<0>(tuple);

    const auto& address = std::get<1>(tuple);
    if (!address.empty()) {
      recip.lpszAddress = const_cast<PWSTR>(address.c_str());
    }
    const auto& name = std::get<2>(tuple);
    if (!name.empty()) {
      recip.lpszName = const_cast<PWSTR>(name.c_str());
    }

    recipients.push_back(recip);
  }
  message_->lpRecips = &recipients[0];
  message_->nRecipCount = recipients_.size();

  // attachment
  std::vector<MapiFileDescW> attachments;
  for (const auto& file : files_) {
    MapiFileDescW attachment;
    ZeroMemory(&attachment, sizeof(MapiFileDescW));
    attachment.nPosition = std::numeric_limits<size_t>::max();
    attachment.lpszPathName = const_cast<PWSTR>(file.c_str());

    attachments.push_back(attachment);
  }
  message_->lpFiles = &attachments[0];
  message_->nFileCount = files_.size();

  auto ret = MAPISendMailWPtr(0, 0, message_, MAPI_LOGON_UI | MAPI_DIALOG, 0);
  if (ret != SUCCESS_SUCCESS) {
    std::cerr << "Send mail failed: " << err_string[ret] << "[" << ret << "]"
              << std::endl;
  }
}
