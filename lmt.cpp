#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#include "RandomPairs.h"
#include "Score.h"

size_t skip_spaces(std::string &str, size_t idx) {
  while (std::isspace(str[idx]) != 0) {
    ++idx;
  }
  return idx;
}

constexpr const char *NOT_A_NUMBER_MSG = "Не число";
constexpr const char *OUT_OF_RANGE_MSG = "Слишком большое число";
constexpr const char *REPEAT_EX = "Еще раз";

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
  std::cout << number << " из " << qty << ":    " << base << " x " << mul << " = ";
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
  RandomPairs randomPairs;
  while (1) {
    try {
      std::cout << "На какое число: ";
      int base = read_int();
      if (base == 0) {
        break;
      }
      std::cout << "Количество примеров: ";
      int times = read_int();
      randomPairs.addBase(base, times);
    } catch (const std::exception &e) {
      std::cout << "Ошибка: неправильное число" << '\n';
      return -1;
    }
  }
  system("clear");
  int ans = 0;
  Score score;
  randomPairs.shuffle();
  int qty = randomPairs.size();
  for (int i = 1; randomPairs.hasNext(); ++i) {
    auto numbers = randomPairs.next();
    int base = numbers.first;
    int mul = numbers.second;
    int correct_ans = base * mul;
    bool parsed = ask(base, mul, i + 1, qty, &ans);
    while (!parsed || ans != correct_ans) {
      if (parsed) {
        std::cout << "Неверно, еще попытка.\n";
        score.mistake_cnt++;
      } else {
        ++score.amending_cnt;
      }
      parsed = ask(base, mul, i + 1, qty, &ans);
    }
    system("clear");
    ++score.correct_ans_cnt;
  }
  score.print();
}
