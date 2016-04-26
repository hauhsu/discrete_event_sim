#include <iostream>
#include <vector>
#include <cmath>
#include "../src/PRNG.h"
#include "statistic.h"

int main(int argc, char *argv[])
{

  RandNumGen::RandGen rand1;
  rand1.rand_stream();

  RandNumGen::RandGen rand2;
  rand2.rand_stream();

  const double u1 = 1;
  const double u2 = 2;

  const double lo1 = 1;
  const double lo2 = 2;

  const double correlation = 4;

  const double NUM_RAND = 100000;
  std::vector<double> X1, X2;
  for (int i = 0; i < NUM_RAND; ++i) {
    auto r1 = rand1.rand();
    auto r2 = rand2.rand();

    auto z1 = pow((-2.0 * log(r1)), 0.5) * cos(2 * M_PI * r2);
    auto z2 = pow((-2.0 * log(r1)), 0.5) * sin(2 * M_PI * r2);

    auto x1 = u1 + lo1 * z1;
    auto x2 = u2 + lo2 * (correlation*z1 + pow( (1 - correlation*correlation), 0.5) * z2);


    X1.push_back(x1);
    X2.push_back(x2);
  }
  
  const auto low(-10), high(10);
  const double region_size = 0.1;
    auto region = build_region(low, high, region_size);
    auto s1 = build_distribution(X1, low, high, region_size);
    auto s2 = build_distribution(X2, low, high, region_size);

  for (int i = 0; i < region.size(); ++i) {
    std::cout << region[i] << ", " << s1[i] << ", " << s2[i] << std::endl;
  }

  return 0;
}
