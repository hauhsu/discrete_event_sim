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

  double mean = 0;
  double covariance = 1.2;
  double phi = 0.25;

  double x1_variance = pow((covariance*covariance) / (1 - phi*phi), 0.5);

  std::vector<double> X1, X2;

  const int NUM_RAND = 10000;
  for (int i = 0; i < NUM_RAND; ++i) {
    auto r1 = rand1.rand();
    auto r2 = rand2.rand();

    auto z1 = pow((-2.0 * log(r1)), 0.5) * cos(2 * M_PI * r2);
    auto z2 = pow((-2.0 * log(r1)), 0.5) * sin(2 * M_PI * r2);

    auto x1 = mean + x1_variance * z1;
    auto epsilon = z2 * pow(covariance, 0.5);
    auto x2 = mean + covariance*(x1 - mean) + epsilon;

    X1.push_back(x1);
    X2.push_back(x2);

    
  }

  const int REGION_SIZE = 100;
  std::vector<double> region(REGION_SIZE);
  for (int i = 0; i < REGION_SIZE; i++) {
    region[i] = (i - REGION_SIZE/2)/10.0;
  }


  std::vector<int> s1 = build_distribution(X1, 0.1, 100);
  std::vector<int> s2 = build_distribution(X2, 0.1, 100);
  
  /*
  std::vector<int> s1(REGION_SIZE, 0);
  std::vector<int> s2(REGION_SIZE, 0);

  for (int t = 0; t < NUM_RAND; t++) {
    for (int i = 0; i < REGION_SIZE; ++i) 
    {
        if (X1[t] < region[i]) {
          s1[i] ++;
          break;
        }
    }
  }

  for (int t = 0; t < NUM_RAND; t++) {
    for (int i = 0; i < REGION_SIZE; ++i) 
    {
        if (X2[t] < region[i]) {
          s2[i] ++;
          break;
        }
    }
  }
  */


  for (int i = 0; i < REGION_SIZE; ++i) {
    std::cout << region[i] << ", " << s1[i] << ", " << s2[i] << std::endl;
  }


  
  return 0;
}

