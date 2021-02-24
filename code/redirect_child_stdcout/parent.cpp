#include <chrono>
#include <stdio.h>
#include <string>
#include <strsafe.h>
#include <tchar.h>
#include <thread>
#include <vcruntime.h>
#include <windows.h>

#define BUFSIZE 4096

HANDLE g_hChildStd_IN_Rd = nullptr;
HANDLE g_hChildStd_IN_Wr = nullptr;
HANDLE g_hChildStd_OUT_Rd = nullptr;
HANDLE g_hChildStd_OUT_Wr = nullptr;

HANDLE g_hInputFile = nullptr;

void CreateChildProcess();
void WriteToPipe();
void ReadFromPipe();
void ErrorExit(PTSTR);
std::string get_resource(std::string&& file_name);

auto _tmain(int argc, TCHAR* argv[]) -> int {
  SECURITY_ATTRIBUTES saAttr;

  printf("\n->Start of parent execution.\n");

  // Set the bInheritHandle flag so pipe handles are inherited.

  saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
  saAttr.bInheritHandle = TRUE;
  saAttr.lpSecurityDescriptor = nullptr;

  // Create a pipe for the child process's STDOUT.

  if (CreatePipe(&g_hChildStd_OUT_Rd, &g_hChildStd_OUT_Wr, &saAttr, 0) == 0)
    ErrorExit(TEXT("StdoutRd CreatePipe"));

  // Ensure the read handle to the pipe for STDOUT is not inherited.

  if (SetHandleInformation(g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0) == 0)
    ErrorExit(TEXT("Stdout SetHandleInformation"));

  // Create a pipe for the child process's STDIN.

  if (CreatePipe(&g_hChildStd_IN_Rd, &g_hChildStd_IN_Wr, &saAttr, 0) == 0)
    ErrorExit(TEXT("Stdin CreatePipe"));

  // Ensure the write handle to the pipe for STDIN is not inherited.

  if (SetHandleInformation(g_hChildStd_IN_Wr, HANDLE_FLAG_INHERIT, 0) == 0)
    ErrorExit(TEXT("Stdin SetHandleInformation"));

  // Create the child process.

  CreateChildProcess();

  // Get a handle to an input file for the parent.
  // This example assumes a plain text file and uses string output to verify data flow.

  // if (argc == 1)
  //   ErrorExit(TEXT("Please specify an input file.\n"));
  const auto input = get_resource("input.txt");

  g_hInputFile = CreateFile(input.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, nullptr);

  if (g_hInputFile == INVALID_HANDLE_VALUE)
    ErrorExit(TEXT("CreateFile"));

  // Write to the pipe that is the standard input for a child process.
  // Data is written to the pipe's buffers, so it is not necessary to wait
  // until the child process is running before writing data.

  std::thread(WriteToPipe).detach();
  printf("\n->Contents of %s written to child STDIN pipe.\n", input.c_str());

  // Read from pipe that is the standard output for child process.

  printf("\n->Contents of child process STDOUT:\n\n");
  ReadFromPipe();

  printf("\n->End of parent execution.\n");

  // The remaining open handles are cleaned up when this process terminates.
  // To avoid resource leaks in a larger application, close handles explicitly.

  return 0;
}

void CreateChildProcess()
// Create a child process that uses the previously created pipes for STDIN and STDOUT.
{
  TCHAR szCmdline[] = TEXT("child");
  PROCESS_INFORMATION piProcInfo;
  STARTUPINFO siStartInfo;
  BOOL bSuccess = FALSE;

  // Set up members of the PROCESS_INFORMATION structure.

  ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

  // Set up members of the STARTUPINFO structure.
  // This structure specifies the STDIN and STDOUT handles for redirection.

  ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
  siStartInfo.cb = sizeof(STARTUPINFO);
  siStartInfo.hStdError = g_hChildStd_OUT_Wr;
  siStartInfo.hStdOutput = nullptr;
  siStartInfo.hStdInput = g_hChildStd_IN_Rd;
  // siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

  // Create the child process.

  bSuccess = CreateProcess(nullptr,
                           szCmdline,    // command line
                           nullptr,      // process security attributes
                           nullptr,      // primary thread security attributes
                           TRUE,         // handles are inherited
                           0,            // creation flags
                           nullptr,      // use parent's environment
                           nullptr,      // use parent's current directory
                           &siStartInfo, // STARTUPINFO pointer
                           &piProcInfo); // receives PROCESS_INFORMATION

  // If an error occurs, exit the application.
  if (bSuccess == 0)
    ErrorExit(TEXT("CreateProcess"));
  else {
    // Close handles to the child process and its primary thread.
    // Some applications might keep these handles to monitor the status
    // of the child process, for example.

    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);

    // Close handles to the stdin and stdout pipes no longer needed by the child process.
    // If they are not explicitly closed, there is no way to recognize that the child process has ended.

    CloseHandle(g_hChildStd_OUT_Wr);
    CloseHandle(g_hChildStd_IN_Rd);
  }
}

void WriteToPipe()

// Read from a file and write its contents to the pipe for the child's STDIN.
// Stop when there is no more data.
{
  DWORD dwRead;
  DWORD dwWritten;
  CHAR chBuf[BUFSIZE];
  BOOL bSuccess = FALSE;

  size_t total_write = 0;

  for (;;) {
    bSuccess = ReadFile(g_hInputFile, chBuf, BUFSIZE, &dwRead, nullptr);
    if ((bSuccess == 0) || dwRead == 0)
      break;
    chBuf[dwRead] = 0;
    while (true) {
      bSuccess = WriteFile(g_hChildStd_IN_Wr, chBuf, dwRead, &dwWritten, nullptr);
      total_write += dwWritten;
      printf("parent wirte to pipe:%s, total size:%zu\n", chBuf, total_write);
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    // if (bSuccess == 0)
    // break;
  }

  // Close the pipe handle so the child process stops reading.

  if (CloseHandle(g_hChildStd_IN_Wr) == 0)
    ErrorExit(TEXT("StdInWr CloseHandle"));
}

void ReadFromPipe()

// Read output from the child process's pipe for STDOUT
// and write to the parent process's pipe for STDOUT.
// Stop when there is no more data.
{
  DWORD dwRead;
  DWORD dwWritten;
  CHAR chBuf[BUFSIZE];
  BOOL bSuccess = FALSE;
  HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  for (;;) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    continue;
    bSuccess = ReadFile(g_hChildStd_OUT_Rd, chBuf, BUFSIZE, &dwRead, nullptr);
    if ((bSuccess == 0) || dwRead == 0)
      break;

    printf("read from child\n");
    bSuccess = WriteFile(hParentStdOut, chBuf, dwRead, &dwWritten, nullptr);
    if (bSuccess == 0)
      break;
  }
}

void ErrorExit(PTSTR lpszFunction)

// Format a readable error message, display a message box,
// and exit from the application.
{
  LPVOID lpMsgBuf;
  LPVOID lpDisplayBuf;
  DWORD dw = GetLastError();

  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr,
                dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, nullptr);

  lpDisplayBuf = (LPVOID) LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR) lpMsgBuf) + lstrlen((LPCTSTR) lpszFunction) + 40)
                                                      * sizeof(TCHAR));
  StringCchPrintf((LPTSTR) lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("%s failed with error %d: %s"),
                  lpszFunction, dw, lpMsgBuf);
  MessageBox(nullptr, (LPCTSTR) lpDisplayBuf, TEXT("Error"), MB_OK);

  LocalFree(lpMsgBuf);
  LocalFree(lpDisplayBuf);
  ExitProcess(1);
}

auto get_resource(std::string&& file_name) -> std::string {
  return std::string(ROOT_DIR) + file_name;
}