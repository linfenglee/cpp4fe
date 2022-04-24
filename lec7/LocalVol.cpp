#include "LocalVol.h"
#include <cmath>

double LocalVol::LV(double t, double s)
{
  double imp = iv.Vol(t, s);
  double dvdk = iv.dVoldK(t, s);
  double dvdt = iv.dVoldT(t, s);
  double d2vdk2 = iv.dVol2dK2(t, s);
  double d1 = (std::log(S0/s) + (rd-rf)*t + 0.5 * imp * imp * t ) / imp / std::sqrt(t);
  double nominator = imp*imp + 2 * t * imp * dvdt + 2 * (rd - rf) * s * t * imp * dvdk;
  double denominator = std::pow(1+s*d1*t*dvdk, 2) + s * s * t * imp * (d2vdk2 - d1 * dvdk * dvdk);
  return std::sqrt(nominator / denominator);    
}
