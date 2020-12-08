#include <filesystem> // If you don't use C++17, GET WITH THE TIMES
#include <fstream>
#include <iostream>
#include <string>

std::string repeat(char repeat, int times) {
  std::string out{};
  for (int iii{}; iii < times; ++iii)
    out += repeat;
  return out;
}

int main() {
  std::cout << "This program will help demonstrate pointers in C++ (maybe)\n\n";
  std::cout << "Degree of pointer depth (5 is *****ptr): ";

  int depth{};
  for (; depth <= 0;) {
    std::cin >> depth;
    std::cin.get();
  }

  std::string file_name;
  std::cout << "\nName of file to write to (default is test.cpp): ";
  std::getline(std::cin, file_name);

  std::fstream write_to;

  if (std::filesystem::exists(file_name)) {
    char choice{'a'};
    while (
        !(choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')) {
      std::cout << "Is it okay to erase all the contents in the file? [Y/N] ";
      std::cin.get(choice);
      if (choice == 'Y' || choice == 'y') {
        write_to.open(file_name, std::ios_base::out | std::ios_base::trunc);
      } else if (choice == 'N' || choice == 'n') {
        write_to.open(file_name, std::ios_base::app);
      }
    }
  } else {
    write_to.open(file_name, std::ios_base::out);
  }
  write_to << "#include <iostream>\n"
              "\nint main() {"
              "\n    int var = 5;"
              "\n    int *ptr1 = &var;";

  for (int iii{2}; iii <= depth; ++iii) {
    write_to << "\n    int " + repeat('*', iii) + "ptr" + std::to_string(iii) +
                    " = &ptr" + std::to_string(iii - 1) + ';';
  }

  write_to << "\n\n    std::cout << " + repeat('*', depth) + "ptr" +
                  std::to_string(depth) + ";\n    return 0;\n}\n";

  write_to.close();
}
