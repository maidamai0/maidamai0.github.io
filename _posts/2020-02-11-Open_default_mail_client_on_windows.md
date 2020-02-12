---
layout: post
---

# Open a default mail client on windows10

In this article I will introduce 3 ways to open mail client on windows:

1. mailto:
2. mapi
3. regestry

## Comparision

1. mailto is a protocal to open a mail client which is surpported by most clients, but no attachment can be specifed.
2. MAPI is suited for MicroSoft Office development, so it is good surpported by Micosoft Ofice suites.
3. registry has the default mail client, so you can use command line options to handle the email.

## Code example(with Qt)

[source](../code/open_default_mail_client_on_windows/README.md)

## Reference

[mailto wiki](https://en.wikipedia.org/wiki/Mailto)

[mailto protocal(rfc6068)](https://tools.ietf.org/html/rfc6068)

[MAPI reference](https://docs.microsoft.com/en-us/cpp/mfc/mapi?view=vs-2019)

[MAPI of outlook](https://docs.microsoft.com/en-us/office/client-developer/outlook/mapi/outlook-mapi-reference)

[mail regestry](https://stackoverflow.com/questions/4819450/launch-default-email-client-to-open-a-send-email-window-with-a-pre-selected-fi#)