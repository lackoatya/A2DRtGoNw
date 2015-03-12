#include <iostream>

void tabulate(int _level) {
  while (_level--) {
    std::cout << "\t";
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) std::cout << "Not enough arguments!";
  else
  {
    int tab_level = 0;
    std::cout << "#pragma once\n\n";

    int ns = 0;
    for (; ns < argc - 2; ++ns) {
      tabulate(tab_level); std::cout << "namespace " << argv[ns + 2] << std::endl;
      tabulate(tab_level); std::cout << "{\n";
      tab_level++;
    }

    tabulate(tab_level); std::cout << "class " << argv[1] << std::endl;
    tabulate(tab_level); std::cout << "{" << std::endl;
    tabulate(tab_level); std::cout << "public:" << std::endl;

    tab_level++;
    tabulate(tab_level); std::cout << "// Constructor" << std::endl;
    tabulate(tab_level); std::cout << "inline " << argv[1] << "(void) = delete;" << std::endl;
    tabulate(tab_level); std::cout << "// Copy Constructor" << std::endl;
    tabulate(tab_level); std::cout << "inline " << argv[1] << "(" << argv[1] << " && _other) = delete;" << std::endl;
    tabulate(tab_level); std::cout << "inline " << argv[1] << "(" << argv[1] << " const& _other) = delete;" << std::endl;
    tabulate(tab_level); std::cout << "// Assignment operator" << std::endl;
    tabulate(tab_level); std::cout << "inline " << argv[1] << " & operator=(" << argv[1] << " && _other) = delete;" << std::endl;
    tabulate(tab_level); std::cout << "inline " << argv[1] << " & operator=(" << argv[1] << " const& _other) = delete;" << std::endl;
    tabulate(tab_level); std::cout << "// Destructor" << std::endl;
    tabulate(tab_level); std::cout << "inline virtual ~" << argv[1] << "(void) = delete;" << std::endl;
    tab_level--;

    tabulate(tab_level); std::cout << "};" << std::endl;

    ns = 0;
    for (; ns < argc - 2; ++ns) {
      tab_level--;
      tabulate(tab_level); std::cout << "}" << std::endl;
    }
  }
  return 0;
}