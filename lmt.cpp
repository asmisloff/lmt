#include <cctype>
#include <iostream>
#include <stdexcept>

#include "RandomPairs.h"
#include "Reader.h"
#include "Score.h"
#include "Timer.h"

constexpr const char *REPEAT_EX = "Еще раз";
constexpr const char *OUT_OF_RANGE_MSG = "Слишком большое число";

static Reader reader;
static RandomPairs random_pairs;
static Timer timer;
static Score score;

bool ask(const int base, const int mul, const int number, const int qty, int *ans) {
  std::cout << number << " из " << qty << ":    " << base << " x " << mul << " = ";
  try {
    *ans = reader.read_int();
  } catch (const std::invalid_argument &e) {
    std::cout << e.what() << ". " << REPEAT_EX << ".\n";
    return false;
  } catch (const std::out_of_range &e) {
    std::cout << OUT_OF_RANGE_MSG << ". " << REPEAT_EX << ".\n";
    return false;
  }
  return true;
}

bool non_negative(int val) {
  return val >= 0;
}

bool positive(int val) {
  return val > 0;
}

bool add_base() {
  int base;
  int times;
  do {
    std::cin.clear();
    std::cout << "На какое число (0 для продолжения): ";
  } while (!reader.try_read_int(&base, non_negative));
  if (base == 0) {
    return false;
  }
  do {
    std::cin.clear();
    std::cout << "Количество примеров: ";
  } while (!reader.try_read_int(&times, positive));
  random_pairs.addBase(base, times);
  return true;
}

void on_expire() {
  std::cout << "Время вышло, для продолжения нажмите Enter.\n";
  reader.new_line_is_zero(true);
}

int main() {
  system("clear");
  while (add_base()) {
  }
  system("clear");
  int ans = 0;
  int qty = random_pairs.size();
  for (int i = 1; random_pairs.hasNext(); ++i) {
    auto numbers = random_pairs.next();
    int base = numbers.first;
    int mul = numbers.second;
    int correct_ans = base * mul;
    timer.count(5000, on_expire);
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
