#include <iostream>
#include <string>

struct Score {
  
  int mistake_cnt = 0;
  int correct_ans_cnt = 0;

  void print() const {
    std::string mark("5");
    if (mistake_cnt > 3) {
      mark = "2";
    } else if (mistake_cnt > 2) {
      mark = "3";
    } else if (mistake_cnt >= 1) {
      mark = "4";
    }
    if (mistake_cnt > 0) {
      std::cout << mistake_cnt << " неправильных ответов\n";
    }
    std::cout << "Оценка: " << mark << std::endl;
  }
};