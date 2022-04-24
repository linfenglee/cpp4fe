#include "ImpliedVol.h"
#include "LocalVol.h"
#include "BSAnalytics.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <utility>
#include <random>

using namespace std;

// we take number of paths and number of time steps as input
std::pair<double,double>
mcLocalVol( function<double(double)> payoff, int nPaths, int nT
	  , double S, double T, double r, double q, const LocalVol& lv)
{
  // Generate a normal distribution
  std::seed_seq seed{5};
  std::mt19937 e(seed);
  std::normal_distribution<> normal_dist(0, 1);
  
  double sum = 0;
  double hsquare = 0;
  double dt = T / nT;
  for(int i = 0; i < nPaths; i++) {
    // for each path, we simulate until maturity T
    double X = std::log(S);
    for(int j = 1; j <= nT; j++) {
      double sigma = lv.LV((j-1)*dt, std::exp(X)); // query local vol
      //      std::cout << (j-1)*dt << "\t" << 100 << "\t" << sigma << std::endl;
      double a = (r - q - 0.5 * sigma * sigma) * dt; // drift term
      double b = normal_dist(e) * sqrt(dt) * sigma;  // diffusion term
      X += a + b; // update state variable
    }
    double h = payoff(std::exp(X));
    sum += h;
    hsquare += h*h;
  }
  double pv = std::exp(-r*T) * sum / nPaths;
  double stderr = sqrt((hsquare / nPaths - (sum/nPaths)*(sum/nPaths))/nPaths);
  return std::pair<double, double>(pv, stderr);
}


int main()
{
  // set up marks for smiles, here the marks are hard coded,
  // the project requires to solve for them from the raw market data
  vector< pair<double, double> > marks;
  marks.push_back(pair<double, double>(1.0, 0.15));
  marks.push_back(pair<double, double>(4.0, 0.132));
  marks.push_back(pair<double, double>(6.0, 0.13));
  marks.push_back(pair<double, double>(8.0, 0.135));
  marks.push_back(pair<double, double>(11.0, 0.14));  
  Smile sm(marks);

  marks.clear();
  marks.push_back(pair<double, double>(0.5, 0.18));
  marks.push_back(pair<double, double>(3.4, 0.146));
  marks.push_back(pair<double, double>(6.0, 0.15));
  marks.push_back(pair<double, double>(8.5, 0.153));
  marks.push_back(pair<double, double>(11.3, 0.16));  
  Smile sm2(marks);

  // build implied vol surface
  vector< pair<double, Smile> > pillarSmiles;
  pillarSmiles.push_back( pair<double, Smile>(1.0, sm) );
  pillarSmiles.push_back( pair<double, Smile>(2.0, sm2) );
  ImpliedVol iv(pillarSmiles);

  // build local vol surface
  double spot = 6;
  double rd = 0.05;
  double rf = 0.02;
  LocalVol lv(iv, spot, rd, rf);

  // now let's price a call option with 1 year maturity
  // here we are not using any structure, it would be better to use our vanilla trade classes
  // and here we hard code the strike, but in the project you would need to calcualte the strike from delta
  double K = 5.2;
  double T = 1;
  auto call = [K](double S){return S>K?S-K:0;};
  // the implied volatility we can query from the implied vol surface
  double sigma = iv.Vol(T, K);
  std::cout << "implied vol = " << sigma << std::endl;
  double bsPrice = bsPricer(Call, K, T, spot, sigma, rd, rf);

  std::cout << "bsPrice = " << bsPrice << std::endl;

  double nPaths = 1024 * 256;
  int nT = 20;
  auto mcResult = mcLocalVol(call, nPaths, nT, spot, T, rd, rf, lv);
  std::cout << "mcPrice = " << mcResult.first << std::endl;

  /*
  // below is to draw the convergence chart
  std::ofstream fout("mcLocalVolError.txt");
  std::ofstream fout2("mcLocalVolSE.txt");
  nPaths = 1024;
  for(int i = 0; i < 12; i++) {
    auto mcResult = mcLocalVol(call, nPaths, nT, spot, T, rd, rf, lv);
    fout << nPaths << "\t" << mcResult.first - bsPrice << std::endl;
    fout2 << nPaths << "\t" << mcResult.second << std::endl;
    nPaths *= 2;
  }
  */
  return 0;
}
