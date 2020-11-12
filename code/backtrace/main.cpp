
// clang-format off
#include <Windows.h>
#include <array>
#include <dbghelp.h>
#include <process.h>
// clang-format on

#include <iostream>
#include <thread>

#include "fmt/format.h"

using namespace std;

constexpr auto trace_max_stack_frames = 32;
constexpr auto trace_max_function_name_length = 1024;

auto print_stack_trace() -> int {
  std::array<void*, trace_max_stack_frames> addresses;

  auto* const process = GetCurrentProcess();
  SymInitialize(process, nullptr, TRUE);

  const auto frames_num = RtlCaptureStackBackTrace(1, trace_max_stack_frames, addresses.data(), nullptr);

  auto* symbol = (SYMBOL_INFO*) malloc(sizeof(SYMBOL_INFO) + (trace_max_function_name_length - 1) * sizeof(TCHAR));
  symbol->MaxNameLen = trace_max_function_name_length;
  symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
  DWORD displacement = 0;
  auto* line = (IMAGEHLP_LINE64*) malloc(sizeof(IMAGEHLP_LINE64));
  line->SizeOfStruct = sizeof(IMAGEHLP_LINE64);
  for (int i = 0; i < frames_num; i++) {
    auto address = (DWORD64)(addresses[i]);
    SymFromAddr(process, address, nullptr, symbol);
    if (SymGetLineFromAddr64(process, address, &displacement, line) != FALSE) {
      fmt::print("{} at {}:{}, {:#x}\n", symbol->Name, line->FileName, line->LineNumber, symbol->Address);
    } else {
      fmt::print("{}, {:#x}\n", symbol->Name, symbol->Address);
    }
  }

  free(symbol);
  free(line);
  return 0;
}

void function_2() {
  fmt::print("stack trace is:\n");
  print_stack_trace();
}

void function_1() {
  function_2();
}

void function_0() {
  function_1();
}

void thread_function() {
  function_0();
}

auto main(int argc, char* argv[]) -> int {
  std::thread(thread_function).join();
}