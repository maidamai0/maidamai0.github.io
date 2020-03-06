#include "open_default_mail_client_cmd.h"

#include "open_with_mapi.h"
#include <iostream>

auto main() -> int {
  MapiClient client;
  client.AddTo(L"123@to.com", L"to");
  client.AddCC(L"123@cc.com", L"cc");
  client.AddBCC(L"123@bcc.com", L"bcc");

  client.AddAtachment(L"C:\\WINDOWS\\System32\\mapi32.dll");
  client.AddAtachment(L"C:\\Windows\\System32\\win32u.dll");

  client.SetBody(L"This is a body");
  client.SetSubject(L"This is a subject");
  client.SendMail();

  return 0;

  OpenDefaultMailClientCmd cmd("example@mail.com");
  cmd.SetSubject("Test");
}