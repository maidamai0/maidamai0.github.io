#include "fmt/core.h"
#include <vector>

class Foo {
public:
  [[nodiscard]] auto GetList() -> std::vector<int>& {
    return list_;
  }

  [[nodiscard]] auto GetListByPointer() -> std::vector<int>* {
    return &list_;
  }

  void Print() const {
    fmt::print("list content is:\n");
    for (const auto& value : list_) {
      fmt::print("{} ", value);
    }
    fmt::print("\n");
  }

private:
  std::vector<int> list_{1, 2, 3};
};

auto main(int argc, char** argv) -> int {
  Foo foo;

  // original
  fmt::print("Original ");
  foo.Print();

  // raw auto
  Foo foo_raw;
  auto list = foo_raw.GetList();
  list.insert(list.end(), {4, 5, 6, 7});
  fmt::print("Raw auto ");
  foo_raw.Print();

  // auto with referecne
  Foo foo_ref;
  auto& list_ref = foo_ref.GetList();
  list_ref.insert(list_ref.end(), {4, 5, 6, 7});
  fmt::print("Reference auto ");
  foo_ref.Print();

  // pointer
  Foo foo_ptr;
  auto list_ptr = foo_ptr.GetListByPointer();
  list_ptr->insert(list_ptr->end(), {4, 5, 6, 7});
  fmt::print("Pointer ");
  foo_ptr.Print();
}