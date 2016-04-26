#include <iostream>
#include <vector>
#include <cmath>
#include "../src/PRNG.h"
#include "statistic.h"

int main(int argc, char *argv[])
{
  RandNumGen::RandGen rand1;
  RandNumGen::RandGen rand2;

  rand1.rand_stream();
  rand2.rand_stream();



  double lambda = 0.8;
  double phi = 0.3;

  int RAND_NUM = 10000;
  std::vector<double> X;
  X.push_back(0.13);

  for (int i = 1; i < RAND_NUM; ++i) {
    double x;
    if (rand1.rand() < phi) {
      x = X[i-1] * phi;
    } else {
      x = X[i-1] * phi + rand2.rand_exp_distribuiton(lambda);
    }

    X.push_back(x);
  }


  auto region = build_region(0, 8, 0.1);
  auto s = build_distribution(X, 0, 8, 0.1);


  for (int i = 0; i < region.size(); ++i) {
    std::cout << region[i] << ", " << s[i] << std::endl;
  }

  return 0;
}
