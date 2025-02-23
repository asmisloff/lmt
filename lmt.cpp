#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

#include "RandomPairs.h"
#include "Score.h"
#include "Timer.h"

size_t skip_spaces(std::string &str, size_t idx) {
  while (std::isspace(str[idx]) != 0) {
    ++idx;
  }
  return idx;
}

static bool treat_new_line_as_zero = false;
constexpr const char *NOT_A_NUMBER_MSG = "Не число";
constexpr const char *OUT_OF_RANGE_MSG = "Слишком большое число";
constexpr const char *REPEAT_EX = "Еще раз";

bool is_blank(const std::string &str) {
  for (auto c : str) {
    if (std::isspace(c) == 0) {
      return false;
    }
  }
  return true;
}

int read_int() {
  std::string input;
  std::getline(std::cin, input);
  while (is_blank(input)) {
    if (treat_new_line_as_zero && is_blank(input)) {
      treat_new_line_as_zero = false;
      return 0;
    }
    std::getline(std::cin, input);
  }
  size_t idx = 0;
  int val = std::stoi(input, &idx);
  while (idx < input.size()) {
    if (std::isspace(input[idx]) == 0) {
      throw std::invalid_argument(NOT_A_NUMBER_MSG);
    }
  }
  return val;
}

bool ask(const int base, const int mul, const int number, const int qty, int *ans) {
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
  Timer timer;
  while (1) {
    try {
      std::cout << "На какое число: ";
      int base = read_int();
      if (base < 0) {
        throw std::invalid_argument("Нельзя вводить отрицательные числа");
      }
      if (base == 0) {
        break;
      }
      std::cout << "Количество примеров: ";
      int times = read_int();
      randomPairs.addBase(base, times);
    } catch (const std::exception &e) {
      std::cout << (e.what() != nullptr ? e.what() : "Ошибка: неправильное число") << '\n';
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
    timer.count(5000, [] {
      std::cout << "Время вышло, для продолжения нажмите Enter.\n";
      treat_new_line_as_zero = true;
    });
    bool parsed = ask(base, mul, i, qty, &ans);
    while (timer.left() >= 0 && (!parsed || ans != correct_ans)) {
      if (parsed) {
        std::cout << "Неверно, еще попытка.\n";
        score.mistake_cnt++;
      } else {
        ++score.amending_cnt;
      }
      parsed = ask(base, mul, i, qty, &ans);
    }
    std::system("clear");
    if (timer.left() >= 0) {
      ++score.correct_ans_cnt;
    } else {
      ++score.mistake_cnt;
    }
  }
  score.print();
  timer.halt();
}
