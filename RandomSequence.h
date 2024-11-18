#include <cstddef>
#include <random>

#pragma once

class RandomSequence {
 public:
  RandomSequence(int size);
  int next();
  int repeat();

 private:
  std::random_device dev;
  std::mt19937 gen;
  std::vector<int> multpliers;
  size_t idx;
};