#pragma once

enum OptionType{Call, Put};

// function declaration
double cnorm(double x);

double oneStepBinomialTree(OptionType optType, double K, double T, double S_0, double S_u, double S_d, double rate);

double bsPricer(OptionType optType, double K, double T, double S_0, double sigma, double rate);