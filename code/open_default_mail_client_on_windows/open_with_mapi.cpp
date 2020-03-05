
#include "open_with_mapi.h"

#include <memory>
#include <string>

#include <iostream>

namespace {
const std::string mapi_dll_name{"mapi32.dll"};
HMODULE mapi32dll = nullptr;
LPMAPISENDMAILW MAPISendMailWPtr = nullptr;
} // namespace

MapiClient ::MapiClient() {
  load_mapi_dll();
  construct_message();
}

MapiClient::~MapiClient() = default;

auto MapiClient::IsValid() const noexcept -> bool {
  return is_valid_;
}

void MapiClient::load_mapi_dll() {
  // mapi_32_dll_->load();

  // if (!mapi_32_dll_->isLoaded()) {
  //   std::cerr << "load " << mapi_dll_name << "failed" << std::endl;
  //   return;
  // }

  // send_email_func_ = reinterpret_cast<send_funcion_ptr>(
  //   mapi_32_dll_->resolve("MAPISendMailW"));

  // if (send_email_func_ == nullptr) {
  //   std::cerr << "load functin address failed" << std::endl;
  //   return;
  // }

  // load dll
  mapi32dll = LoadLibrary(mapi_dll_name.c_str());
  if (mapi32dll == nullptr) {
    std::cerr << "Load " << mapi_dll_name << " failed" << std::endl;
    return;
  }

  // get functin address
  MAPISendMailWPtr = reinterpret_cast<LPMAPISENDMAILW>(
    GetProcAddress(mapi32dll, "MAPISendMailW"));
  if (MAPISendMailWPtr == nullptr) {
    std::cerr << "Get MAPISendMailW failed" << std::endl;
    FreeLibrary(mapi32dll);
    return;
  }

  is_valid_ = true;
}

void MapiClient::construct_message() {
  message_ = new MapiMessageW();
  message_->lpszSubject = L"Test subject";
  // MapiFileDescW file;
}

void MapiClient::SendMail() {
  auto ret = MAPISendMailWPtr(0, 0, message_, 0, 0);
  if (ret != SUCCESS_SUCCESS) {
    std::cerr << "Send mail failed:" << ret << std::endl;
  }
}
