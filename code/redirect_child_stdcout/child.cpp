#include <chrono>
#include <cstdio>
#include <thread>
#include <windows.h>

#define BUFSIZE 4096

auto main() -> int {
  CHAR chBuf[BUFSIZE];
  DWORD dwRead;
  DWORD dwWritten;
  HANDLE hStdin;
  HANDLE hStdout;
  BOOL bSuccess;

  hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
  hStdin = GetStdHandle(STD_INPUT_HANDLE);
  if ((hStdout == INVALID_HANDLE_VALUE) || (hStdin == INVALID_HANDLE_VALUE))
    ExitProcess(1);

  // Send something to this process's stdout using printf.
  printf("\n ** This is a message from the child process. ** \n");

  // This simple algorithm uses the existence of the pipes to control execution.
  // It relies on the pipe buffers to ensure that no data is lost.
  // Larger applications would use more advanced process control.

  for (;;) {
    // Read from standard input and stop on error or no data.
    bSuccess = ReadFile(hStdin, chBuf, BUFSIZE, &dwRead, nullptr);
    chBuf[dwRead] = 0;
    printf("child read:\n");
    printf("%s", chBuf);

    if ((bSuccess == 0) || dwRead == 0)
      break;

    // Write to standard output and stop on error.
    bSuccess = WriteFile(hStdout, chBuf, dwRead, &dwWritten, nullptr);

    if (bSuccess == 0)
      break;
  }
  return 0;
}