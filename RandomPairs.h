#include <cstddef>
#include <random>
#include <vector>
class RandomPairs {
 public:
  RandomPairs();
  void addBase(int base, int cnt);
  void shuffle();
  std::pair<int, int> next();
  bool hasNext() const;
  size_t size() const;

 private:
  std::vector<int> bases;
  std::vector<int> multipliers;
  std::random_device rd;
  std::mt19937 g;
  std::uniform_int_distribution<> dist;
};