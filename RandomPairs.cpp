#include "./RandomPairs.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <random>
#include <utility>

RandomPairs::RandomPairs() 
  : g{std::mt19937(rd())}
  , dist{std::uniform_int_distribution<>(1, 10)}
  {}

void RandomPairs::addBase(int base, int cnt) {
  assert(base > 1 && base < 10);
  assert(cnt > 0 && cnt < 100);
  int m = dist(g);
  while (cnt-- > 0) {
    bases.push_back(base);
    multipliers.push_back(m++);
    if (m == 10) {
      m = 1;
    }
  }
}

void RandomPairs::shuffle() { 
  std::shuffle(bases.begin(), bases.end(), g);
  std::shuffle(multipliers.begin(), multipliers.end(), g);
}

bool RandomPairs::hasNext() const { return !bases.empty(); }

std::pair<int, int> RandomPairs::next() {
  int base = bases.back();
  int m = multipliers.back();
  bases.pop_back();
  multipliers.pop_back();
  return { base, m };
}

size_t RandomPairs::size() const {
  return bases.size();
}