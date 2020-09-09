#include "sstream"
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

auto write(std::ostream& of, std::string&& content) {
  const auto current_pos = of.tellp();
  std::cout << "current positon is " << current_pos << std::endl;
  if (current_pos == 0) {
    // file is empty
    of << '[' << content << ']';
    of.flush();
    return;
  }

  // remove last ']'
  of.seekp(-1, std::ios_base::end);

  // append a `,` first
  // append a `]` last
  of << ',' << content << ']';
  of.flush();
}

auto main(int argc, char** argv) -> int {
  std::ofstream of("test.json");

  for (int i = 0; i < 5; ++i) {
    write(of, R"({"number":)" + std::to_string(i) + '}');
  }

  {
    std::stringstream ss(" fjdf");
    char c = ss.peek();
    std::cout << "peek:" << c << std::endl;
  }

  {
    std::stringstream ss(" fjdf");
    char c = ss.get();
    std::cout << "get:" << c << std::endl;
  }

  {
    std::istringstream ss(" fjdf");
    char c;
    ss >> c;
    std::cout << "<<:" << c << std::endl;
  }
}