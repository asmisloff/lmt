#include <algorithm>
#include <random>
#include <vector>

#include "RandomSequence.h"

constexpr int MIN_MULTIPLIER = 1;
constexpr int MAX_MULTIPLIER = 10;

RandomSequence::RandomSequence(int size)
    : dev{std::random_device()}
    , gen{std::mt19937(dev())}
    , multpliers{std::vector<int>(size)}
    , idx{0}
{
  std::uniform_int_distribution<> dist(MIN_MULTIPLIER, MAX_MULTIPLIER);
  int mul = dist(gen);
  for (int &iter : multpliers) {
    iter = mul;
    ++mul;
    if (mul > MAX_MULTIPLIER) {
      mul = MIN_MULTIPLIER;
    }
  }
  std::shuffle(multpliers.begin(), multpliers.end(), gen);
}

int RandomSequence::next() {
  return multpliers[idx++];
}