#include <iostream>
#include <cassert> // for assertion on inputs

#include "one_step_bt.h"

int main()
{
    OptionType optType;
    double K, T, S_0, S_u, S_d, rate, V_u, V_d, sigma;
    std::cout << "option type (0 for Call and 1 for Put): ";
    int optType_;
    std::cin >> optType_;
    assert(optType_ == 0 || optType_ == 1);
    optType = static_cast<OptionType>(optType_);
    std::cout << "strke: ";
    std::cin >> K;
    std::cout << "time to maturity: ";
    std::cin >> T;
    std::cout << "current value of the underlying stock: ";
    std::cin >> S_0;
    std::cout << "risk free interest rate: ";
    std::cin >> rate;
    std::cout << "up state: ";
    std::cin >> S_u;
    std::cout << "down state: ";
    std::cin >> S_d;
    std::cout << "volatility: ";
    std::cin >> sigma;

    double V_tree = oneStepBinomialTree(optType, K, T, S_0, S_u, S_d, rate);
    double V_bs = bsPricer(optType, K, T, S_0, sigma, rate);
    std::cout << "The option price of one step binomial tree is " << V_tree << std::endl;
    std::cout << "The option price of black-scholes formula is " << V_bs << std::endl;
    return 0;
}