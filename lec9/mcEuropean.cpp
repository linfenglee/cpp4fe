#include <iostream>
#include <fstream>
#include <random>
#include <cmath>
#include <utility>
#include <functional>
#include "BSAnalytics.h"

std::pair<double,double> mcEuropean(std::function<double(double)> payoff, int nPaths
		 , double S, double T, double r, double q, double sigma)
{
  // Generate a normal distribution around that mean
  std::seed_seq seed{5};
  std::mt19937 e(seed);
  std::normal_distribution<> normal_dist(0, 1);
  double sum = 0.0;
  double hsquare = 0.0;
  for(int i = 0; i < nPaths; i++) {
    double wT = normal_dist(e) * sqrt(T);
    double h = payoff(S*std::exp((r-q-0.5*sigma*sigma)*T + sigma * wT));
    sum += h;
    hsquare += h*h;
  }
  double pv = std::exp(-r*T) * sum / nPaths;
  double std_err = std::sqrt((hsquare / nPaths - (sum/nPaths)*(sum/nPaths))/nPaths);
  return std::pair<double, double>(pv, std_err);
}


int main()
{
  //  auto call = [](double S){return std::max(S-90, 0);};
  double K = 100;
  auto call = [K](double S){return S>K?S-K:0;};

  double bsPrice = bsPricer(Call, K, 1, 100, 0.15, 0.05, 0.02);
  double nPaths = 1024;
  std::ofstream fout("mcEuropeanError.txt");
  std::ofstream fout2("mcEuropeanSE.txt");
  for(int i = 0; i < 12; i++) {
    auto mcResult = mcEuropean(call, nPaths, 100, 1, 0.05, 0.02, 0.15);
    fout << nPaths << "\t" << mcResult.first - bsPrice << std::endl;
    fout2 << nPaths << "\t" << mcResult.second << std::endl;
    nPaths *= 2;
  }
  return 0;
}
