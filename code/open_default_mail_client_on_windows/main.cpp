#include "open_default_mail_client_cmd.h"

#include "open_with_mapi.h"
#include <iostream>

auto main() -> int {
  MapiClient client;
  client.SendMail();

  int a;
  std::cin >> a;
  return 0;

  OpenDefaultMailClientCmd cmd("example@mail.com");
  cmd.SetSubject("Test");
}