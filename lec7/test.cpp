#include "ImpliedVol.h"
#include "LocalVol.h"
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  vector< pair<double, double> > marks;
  marks.push_back(pair<double, double>(1.0, 0.15));
  marks.push_back(pair<double, double>(4.0, 0.132));
  marks.push_back(pair<double, double>(6.0, 0.13));
  marks.push_back(pair<double, double>(8.0, 0.135));
  marks.push_back(pair<double, double>(11.0, 0.14));  
  Smile sm(marks);

  ofstream fout("smile.txt");
  for (int i = 0; i < 120; i++) {
    double k = 0.2 + 12 / 120.0 * i;
    fout << k << "\t " << sm.Vol(k) << endl;
  }

  ofstream fout2("marks.txt");
  for (int i = 0; i < marks.size(); i++) {
    fout2 << marks[i].first << "\t" << marks[i].second << endl;
  }


  marks.clear();
  marks.push_back(pair<double, double>(0.5, 0.18));
  marks.push_back(pair<double, double>(3.4, 0.146));
  marks.push_back(pair<double, double>(6.0, 0.15));
  marks.push_back(pair<double, double>(8.5, 0.153));
  marks.push_back(pair<double, double>(11.3, 0.16));  
  Smile sm2(marks);

  
  vector< pair<double, Smile> > pillarSmiles;
  pillarSmiles.push_back( pair<double, Smile>(1.0, sm) );
  pillarSmiles.push_back( pair<double, Smile>(2.0, sm2) );  
  ImpliedVol iv(pillarSmiles);

  ofstream fout3("impliedvol.txt");
  for (int i = 0; i < 60; i++) {
    double t = 0.025 + 0.05 * i;
    for (int j = 0; j < 50; j++) {
      double k = 0.2 + 12 / 50.0 * j;
      fout3 << t << "\t" << k << "\t " << iv.Vol(t, k) << endl;
    }
  }

  LocalVol lv(iv, 6.0, 0.03, 0.02);

  ofstream fout4("localvol.txt");
  for (int i = 0; i < 60; i++) {
    double t = 0.025 + 0.05 * i;
    for (int j = 0; j < 50; j++) {
      double k = 0.2 + 12 / 50.0 * j;
      fout4 << t << "\t" << k << "\t " << lv.LV(t, k) << endl;
    }
  }
}
