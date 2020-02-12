#include "open_default_mail_client_cmd.h"

auto main() -> int {
  OpenDefaultMailClientCmd cmd("example@mail.com");
  cmd.SetSubject("Test");
}