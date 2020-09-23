#include "shared.h"
#include "static.h"

#include <iostream>
#include <mutex>

std::mutex mtx;

auto operator new(size_t size) -> void* {
  {
    // std::cout << "Allocating " << size << " bytes\n";
    printf("Allocating %zu bytes\n", size);
  }
  return malloc(size);
}

auto operator delete(void* p, size_t size) -> void {
  {
    std::lock_guard<std::mutex> lock(mtx);
    // std::cout << "Freeing " << size << " bytes\n";
    printf("Freeing %zu bytes\n", size);
  }
  free(p);
}

class Object {
public:
  Object() = default;
  ~Object() = default;

private:
  int a_;
  int b_;
};

auto main(int argc, char** argv) -> int {
  {
    auto* object = new Object();
    delete object;
  }

  return 0;
}