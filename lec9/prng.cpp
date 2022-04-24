#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>

int main()
{
  // Generate a normal distribution around that mean
  std::seed_seq seed{1};
  std::mt19937 e(seed);
  std::normal_distribution<> normal_dist(0, 1);

  std::map<int, int> hist;
  for (int n = 0; n < 10000; ++n)
    ++hist[std::round(normal_dist(e)*2)];
  // generate histogram
  for (auto p : hist) {
    std::cout << std::fixed << std::setprecision(1) << std::setw(4)
	      << p.first / 2.0 << ' ' << std::string(p.second/200, '*') << '\n';
  }
}
