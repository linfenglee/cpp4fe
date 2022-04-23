#include <cmath> // for std::exp()

#include "one_step_bt.h"

double oneStepBinomialTree (OptionType optType, double K, double T, double S_0, double S_u, double S_d, double rate)
{
    double V_u, V_d;
    double q_u = (S_0*std::exp(rate*T) - S_d) / (S_u - S_d);
    switch (optType)
    {
        case Call:
            V_u = S_u > K ? S_u - K : 0;
            V_d = S_d > K ? S_d - K : 0;
            break;
        case Put:
            V_u = S_u < K ? K - S_u : 0;
            V_d = S_d < K ? K - S_d : 0;
            break;
        default:
            throw "unsupported optionType";
    }
    double V_0 = std::exp(-rate * T) * (q_u * V_u + (1-q_u) * V_d);
    return V_0;
}

double bsPricer(OptionType optType, double K, double T, double S_0, double sigma, double rate)
{
    double sigmaSqrtT = sigma * std::sqrt(T);
    double d1 = (std::log(S_0 / K) + rate)/sigmaSqrtT + 0.5 * sigmaSqrtT;
    double d2 = d1 - sigmaSqrtT;

    double V_0;
    switch (optType)
    {
        case Call:
            V_0 = S_0 * cnorm(d1) - K * exp(-rate*T) * cnorm(d2);
            break;
        case Put:
            V_0 = K * exp(-rate*T) * cnorm(-d2) - S_0 * cnorm(-d1);
            break;
        default:
            throw "unsupported optionType";
    }
    return V_0;
}

double cnorm(double x)
{
    // constants
    double a1 =  0.254829592;
    double a2 = -0.284496736;
    double a3 =  1.421413741;
    double a4 = -1.453152027;
    double a5 =  1.061405429;
    double p  =  0.3275911;
    int sign = 1;
    if (x < 0)
        sign = -1;
    x = fabs(x)/sqrt(2.0);
    double t = 1.0/(1.0 + p*x);
    double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);
    return 0.5*(1.0 + sign*y);
}