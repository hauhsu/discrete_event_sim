#include <iostream>
#include <algorithm>
#include "../src/PRNG.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

int main(int argc, char *argv[])
{
  RandNumGen::RandGen rand1;
  rand1.rand_stream();

  RandNumGen::RandGen rand2;
  rand2.rand_stream();

  const int REGION_SIZE = 100;
  std::vector<int> statistic1(REGION_SIZE, 0);
  std::vector<int> statistic2(REGION_SIZE, 0);
  std::vector<double> region(REGION_SIZE);
  for (int i = 0; i < REGION_SIZE; i++) {
    region[i] = (i - REGION_SIZE/2)/10.0;
  }

  
  std::vector<double> norm_dist;
  const double NUM_RAND = 100;
  for (int i = 0; i < NUM_RAND; ++i) {
    auto r1 = rand1.rand();
    auto r2 = rand2.rand();
    auto z1 = pow((-2.0 * log(r1)), 0.5) * cos(2 * M_PI * r2);
    norm_dist.push_back(z1);
    auto z2 = pow((-2.0 * log(r1)), 0.5) * sin(2 * M_PI * r2);
    for (int r = 0; r < REGION_SIZE; r++) {
      if (z1 < region[r]) {
        statistic1[r] ++;
        break;
      }
    }
    for (int r = 0; r < REGION_SIZE; r++) {
      if (z2 < region[r]) {
        statistic2[r] ++;
        break;
      }
    }
  }

  std::sort(norm_dist.begin(), norm_dist.end());
  for (int i = 0; i < NUM_RAND; ++i) {
    auto R = (i - 0.5) / NUM_RAND;
    auto t = (pow(R, 0.135) - pow( (1 - R), 0.135)) / 0.1975; 

    std::cout << norm_dist[i] << ", " << t << std::endl;

  }
  


  /*
  std::cout << " , s1, s2" << std::endl;
  for (int i = 0; i < REGION_SIZE; ++i) {
    std::cout << (i-REGION_SIZE/2)/10.0 << ", " << statistic1[i] / NUM_RAND << ", " << statistic2[i] / NUM_RAND << std::endl;
  }

  */
  return 0;
}
