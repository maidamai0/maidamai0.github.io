// clang-format off
#include <iostream>
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
    MapiRecipDescW recip;
    ::ZeroMemory(&recip, sizeof(recip));
    recip.lpszName = L"QA email";
    recip.lpszAddress = L"qa@myaccount.com";

    // the message
    MapiMessageW msg;
    ::ZeroMemory(&msg, sizeof(msg));
    msg.lpszSubject = L"Test";
    msg.nRecipCount = 1; // if I comment out this line it works fine...
    msg.lpRecips = &recip;
    msg.nFileCount = 1;
    msg.lpFiles = &filedesc;

    const auto ret
      = (*lpfnMAPISendMail)(0, NULL, &msg, MAPI_LOGON_UI | MAPI_DIALOG, 0);

    std::cout << "send result: " << ret << std::endl;

    FreeLibrary(hMapiModule);
  }

  return 0;
}