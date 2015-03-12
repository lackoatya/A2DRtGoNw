#include <string>
#include <fstream>
#include <iostream>
#include <streambuf>

#include "BOOST/foreach.hpp"
#include "BOOST/filesystem.hpp"

void process_file(boost::filesystem::path _file, std::string const& _domain) {
  std::ifstream original_file;
  original_file.open(_file.generic_string());
  std::string content((std::istreambuf_iterator<char>(original_file)),
                      std::istreambuf_iterator<char>());
  original_file.close();

  std::ofstream new_file;
  new_file.open(_file.generic_string(), std::ofstream::out | std::ofstream::trunc);
  new_file << _domain << std::endl << content;
  new_file.close();
}

void process_path(boost::filesystem::path const& current_path, std::string const& _domain) {
  boost::filesystem::directory_iterator iterator(current_path), eod;

  BOOST_FOREACH(boost::filesystem::path const& path, std::make_pair(iterator, eod)) {
    if (boost::filesystem::is_regular_file(path)) {
      if (path.extension().generic_string() == ".h" ||
          path.extension().generic_string() == ".cpp" ||
          path.extension().generic_string() == ".hpp")
        process_file(path, _domain);
    }
    else {
      if (boost::filesystem::is_directory(path))
        process_path(path, _domain);
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    std::ifstream domain_file;
    domain_file.open(argv[1]);
    std::string domain((std::istreambuf_iterator<char>(domain_file)),
                       std::istreambuf_iterator<char>());
    domain_file.close();

    process_path(boost::filesystem::current_path(), domain);
  }
  else {
    std::cout << "Please enter a domain file as argument!";
  }

  return 0;
}