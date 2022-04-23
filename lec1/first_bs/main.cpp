#include <iostream>
#include <cmath> // for std::exp()
#include <cassert> // for assertion on inputs

#include "first_bs.h"

using namespace std;

int main()
{
    OptionType optType;
    double K, T, S_0, sigma, rate;
    cout << "option type (0 for Call and 1 for Put): ";
    int optType_;
    cin >> optType_;
    assert(optType_ == 0 || optType_ == 1);
    optType = static_cast<OptionType>(optType_);  // what does 'static_cast<OptionType>' mean?
    cout << "strike: ";
    cin >> K;
    cout << "time to maturity (in years): ";
    cin >> T;
    cout << "current value of the underlying stock: ";
    cin >> S_0;
    cout << "risk free interest rate: ";
    cin >> rate;
    cout << "volatility: ";
    cin >> sigma;

    double sigmaSqrtT = sigma * sqrt(T);
    double d1 = (log(S_0 / K) + rate * T)/sigmaSqrtT + 0.5 * sigmaSqrtT;
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

    cout << "The option price is " << V_0 << endl;
    return 0;
}