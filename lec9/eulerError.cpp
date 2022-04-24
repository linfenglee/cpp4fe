#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

int main()
{
  // Generate a normal distribution around that mean
  std::seed_seq seed{5};
  std::mt19937 e(seed);
  std::normal_distribution<> normal_dist(0, 1);

  // each time step is 1 day, so standard deviation is sqrt(1/365.0);
  int nT = 5;
  double S0 = 10;
  double sigma = 0.30;
  double drift = 0.1;
  double T = 5.0;
  std::vector<double> exact(nT+1, S0);
  std::vector<double> euler(nT+1, S0);
  std::vector<double> milstein(nT+1, S0);
  std::ofstream fout1("eulerError_Exact.txt");
  std::ofstream fout2("eulerError_Euler.txt");
  std::ofstream fout3("eulerError_Milstein.txt");  
  fout1 << 0 << "\t" << S0 << std::endl;
  fout2 << 0 << "\t" << S0 << std::endl;
  fout3 << 0 << "\t" << S0 << std::endl;
  double dt = T / nT;
  for (int i = 1; i <= nT; i++) {
    double dw = normal_dist(e) * sqrt(dt);
    exact[i] = exact[i-1] * std::exp((drift - 0.5*sigma*sigma)*dt + dw*sigma);
    euler[i] = euler[i-1] * (1 + drift * dt + dw*sigma);
    milstein[i] = milstein[i-1] * (1 + drift*dt + dw*sigma + 0.5*sigma*sigma*(dw*dw - dt));
    fout1 << i*dt << "\t" << exact[i] << std::endl;
    fout2 << i*dt << "\t" << euler[i] << std::endl;
    fout3 << i*dt << "\t" << milstein[i] << std::endl;
  }
  return 0;
}
