#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include <boost/numeric/ublas/matrix.hpp>

using namespace boost::numeric::ublas;

int main()
{
  // Generate a normal distribution around that mean
  std::seed_seq seed{1};
  std::mt19937 e(seed);
  std::normal_distribution<> normal_dist(0, 1);

  // generate 3 brownian motions for 1Y
  matrix<double> brownians(3, 366, 0);
  // each time step is 1 day, so standard deviation is sqrt(1/365.0);
  double stdev = sqrt(1/365.0);
  for (int i = 0; i < brownians.size1(); i++) {
    std::ofstream fout("brownian" + std::to_string(i) + ".txt");
    fout << 0 << "\t" << brownians(i, 0) << std::endl;
    for (int j = 1; j < brownians.size2(); j++) {
      brownians(i, j) = brownians(i, j-1) + normal_dist(e) * stdev;
      fout << j/365.0 << "\t" << brownians(i, j) << std::endl;
    }
  }
  return 0;
}
