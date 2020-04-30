#include "fmt/core.h"

class Foo {
public:
  Foo() = default;

  void f() const {
    static auto cnt = 0;
    fmt::print("cnt is {}\n", ++cnt);
  }
};

auto main(int argc, char** argv) -> int {
  for (int i = 0; i < 5; ++i) {
    Foo foo;
    foo.f();
  }
}