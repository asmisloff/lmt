#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Score {
  
  unsigned int mistake_cnt = 0;
  unsigned int correct_ans_cnt = 0;
  unsigned int amending_cnt = 0;

  void print() const {
    std::string mark = mistake_cnt > marks.size()
      ? "1-"
      : marks[mistake_cnt];
    if (amending_cnt > 0 && mark.back() != '-') {
      mark += '-';
    }
    std::cout << "Всего примеров: " << correct_ans_cnt << "\n"
              << "Неверных ответов: " << mistake_cnt << "\n"
              << "Исправлений: " << amending_cnt << "\n"
              << "Оценка: " << mark << "\n";
  }

  private:
  std::vector<std::string> marks = {
    "5", "5-", "4", "3", "3", "2", "2-", "1", "1-"
  };
};
