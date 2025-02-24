#ifndef READER_H
#define READER_H

#include <string>

class Reader {
 public:
  int read_int(bool (*filter) (int val) = nullptr);
  bool try_read_int(int *res, bool (*filter) (int val) = nullptr);
  inline bool new_line_is_zero() { return treat_new_line_as_zero; }
  inline void new_line_is_zero(bool val) { treat_new_line_as_zero = val; }
 private:
  bool treat_new_line_as_zero = false;
};

#endif