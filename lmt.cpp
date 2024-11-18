#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "RandomSequence.h"
#include "Score.h"

size_t skip_spaces(std::string &str, size_t idx) {
  while (std::isspace(str[idx]) != 0) {
    ++idx;
  }
  return idx;
}

constexpr const char *NOT_A_NUMBER_MSG = "Not a number";
constexpr const char *OUT_OF_RANGE_MSG = "Too big number";
constexpr const char *REPEAT_EX = "Repeat";

int read_int() {
  std::string input;
  std::cin >> input;
  size_t idx = 0;
  int val = std::stoi(input, &idx);
  while (idx < input.size()) {
    if (std::isspace(input[idx]) == 0) {
      throw std::invalid_argument(NOT_A_NUMBER_MSG);
    }
  }
  return val;
}

bool ask(int base, int mul, int number, int qty, int *ans) {
  std::cout << number << " of " << qty << ":    " << base << " x " << mul << " = ";
  try {
    *ans = read_int();
  } catch (const std::invalid_argument &e) {
    std::cout << NOT_A_NUMBER_MSG << ". " << REPEAT_EX << ".\n";
    return false;
  } catch (const std::out_of_range &e) {
    std::cout << OUT_OF_RANGE_MSG << ". " << REPEAT_EX << ".\n";
    return false;
  }
  return true;
}

int main() {
  system("clear");
  int base, times;
  try {
    std::cout << "Base number: ";
    base = read_int();
    std::cout << "Number of exercises: ";
    times = read_int();
  } catch (const std::exception &e) {
    std::cout << "Error: bad number" << '\n';
    return -1;
  }
  system("clear");
  RandomSequence random(times);
  int ans = 0;
  Score score;
  for (int i = 0; i < times; ++i) {
    int mul = random.next();
    int correct_ans = base * mul;
    bool parsed = ask(base, mul, i + 1, times, &ans);
    while (!parsed || ans != correct_ans) {
      if (parsed) {
        std::cout << "Wrong, repeat.\n";
        score.mistake_cnt++;
      }
      parsed = ask(base, mul, i + 1, times, &ans);
    }
    std::cout << "Correct!\n";
    ++score.correct_ans_cnt;
  }
  score.print();
}
