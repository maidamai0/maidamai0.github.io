
#include <iostream>
#include <array>

// clang-format off
#include <tchar.h>
#include <windows.h>
#include <mapi.h>
// clang-format on

auto main(int argc, char** argv) -> int {
  HMODULE hMapiModule = LoadLibrary(_T( "mapi32.dll" ));

  if (hMapiModule != nullptr) {
    LPMAPISENDMAILW lpfnMAPISendMail = nullptr;
    lpfnMAPISendMail
      = (LPMAPISENDMAILW) GetProcAddress(hMapiModule, "MAPISendMailW");

    // file attachment
    MapiFileDescW filedesc;
    ::ZeroMemory(&filedesc, sizeof(filedesc));
    filedesc.nPosition = (ULONG) -1;
    filedesc.lpszPathName = L"C:\\WINDOWS\\System32\\mapi32.dll";

    // recipient(s)
    // std::array<MapiRecipDescW,4> recips;
    MapiRecipDescW recip;
    ZeroMemory(&recip, sizeof(MapiRecipDescW));
    recip.lpszName = L"QA email";
    recip.lpszAddress = L"qa@myaccount.com";
    recip.ulRecipClass = MAPI_TO;

    // the message
    MapiMessageW msg;
    ZeroMemory(&msg, sizeof(msg));
    msg.lpszSubject = L"This is a Subject";
    msg.lpszNoteText = L"This is a note";
    msg.nRecipCount = 1; // if I comment out this line it works fine...
    msg.lpRecips = &recip;
    msg.nFileCount = 1;
    msg.lpFiles = &filedesc;

    const auto ret
      = (*lpfnMAPISendMail)(0, NULL, &msg, MAPI_LOGON_UI | MAPI_DIALOG, 0);

    std::string error;
    switch (ret)
    {
      case SUCCESS_SUCCESS:{
        error = "MAPI Succeed.";
        break;
      }
      case MAPI_USER_ABORT:
        error = "MAPI User Aborted.";
        break;
      case MAPI_E_FAILURE:
        error = "MAPI Failure.";
        break;
      case MAPI_E_LOGIN_FAILURE:
        error = "MAPI Login Failure.";
        break;
      case MAPI_E_DISK_FULL:
        error = "MAPI Disk full.";
        break;
      case MAPI_E_INSUFFICIENT_MEMORY:
        error = "MAPI Insufficient memory.";
        break;
      case MAPI_E_ACCESS_DENIED:
        error = "MAPI Access Denied.";
        break;
      case MAPI_E_TOO_MANY_SESSIONS:
        error = "MAPI Too many sessions.";
        break;
      case MAPI_E_TOO_MANY_FILES:
        error = "MAPI too many files.";
        break;
      case MAPI_E_TOO_MANY_RECIPIENTS:
        error = "MAPI too many recipients.";
        break;
      case MAPI_E_ATTACHMENT_NOT_FOUND:
        error = "MAPI Attachment not found.";
        break;
      case MAPI_E_ATTACHMENT_OPEN_FAILURE:
        error = "MAPI Attachment open failure.";
        break;
      case MAPI_E_ATTACHMENT_WRITE_FAILURE:
        error = "MAPI Attachment Write Failure.";
        break;
      case MAPI_E_UNKNOWN_RECIPIENT:
        error = "MAPI Unknown recipient.";
        break;
      case MAPI_E_BAD_RECIPTYPE:
        error = "MAPI Bad recipient type.";
        break;
      case MAPI_E_NO_MESSAGES:
        error = "MAPI No messages.";
        break;
      case MAPI_E_INVALID_MESSAGE:
        error = "MAPI Invalid message.";
        break;
      case MAPI_E_TEXT_TOO_LARGE:
        error = "MAPI Text too large.";
        break;
      case MAPI_E_INVALID_SESSION:
        error = "MAPI Invalid session.";
        break;
      case MAPI_E_TYPE_NOT_SUPPORTED:
        error = "MAPI Type not supported.";
        break;
      case MAPI_E_AMBIGUOUS_RECIPIENT:
        error = "MAPI Ambiguous recipient.";
        break;
      case MAPI_E_MESSAGE_IN_USE:
        error = "MAPI Message in use.";
        break;
      case MAPI_E_NETWORK_FAILURE:
        error = "MAPI Network failure.";
        break;
      case MAPI_E_INVALID_EDITFIELDS:
        error = "MAPI Invalid edit fields.";
        break;
      case MAPI_E_INVALID_RECIPS:
        error = "MAPI Invalid Recipients.";
        break;
      case MAPI_E_NOT_SUPPORTED:
        error = "MAPI Not supported.";
        break;
      case MAPI_E_UNICODE_NOT_SUPPORTED:
        error = "MAPI Unicode Not Supported.";
        break;
      case MAPI_E_ATTACHMENT_TOO_LARGE:
        error = "MAPI Attachment too Large.";
        break;
    }

    std::cout << "send result: " << &error << std::endl;

    FreeLibrary(hMapiModule);
  }

  return 0;
}