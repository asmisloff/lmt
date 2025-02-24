#include "./Reader.h"
#include <iostream>
#include <stdexcept>

bool is_blank(const std::string &str);
int parse_int(const std::string &str);
constexpr const char *NOT_A_NUMBER_MSG = "Не число";
constexpr const char *OUT_OF_RANGE_MSG = "Число выходит за установленные пределы";

int Reader::read_int(bool (*filter) (int val)) {
  std::string input;
  std::getline(std::cin, input);
  while (is_blank(input)) {
    if (new_line_is_zero() && is_blank(input)) {
      new_line_is_zero(false);
      return 0;
    }
    std::getline(std::cin, input);
  }
  int res = parse_int(input);
  if (filter != nullptr && !filter(res)) {
    throw std::out_of_range(OUT_OF_RANGE_MSG);
  }
  return res;
}


bool Reader::try_read_int(int *res, bool (*filter) (int val)) {
  try {
    *res = read_int(filter);
  } catch (const std::exception &e) {
    std::cout << e.what() << '\n';
    return false;
  }
  return true;
}


bool is_blank(const std::string &str) {
  for (auto c : str) {
    if (std::isspace(c) == 0) {
      return false;
    }
  }
  return true;
}


int parse_int(const std::string &str) {
  size_t idx = 0;
  int res = std::stoi(str, &idx);
  while (idx < str.size()) {
    if (!std::isspace(str[idx])) {
      throw std::invalid_argument(NOT_A_NUMBER_MSG);
    }
  }
  return res;
}
