#include <iostream>
#include <vector>
#include "PRNG.h"

int main(int argc, char *argv[])
{
  RandNumGen::RandGen rand1, rand2;
  rand1.rand_stream();
  rand2.rand_stream();
  

  const int REGION_SIZE = 100;
  std::vector<int> statistic(REGION_SIZE, 0);
  std::vector<double> region(REGION_SIZE);

  for (int i = 0; i < REGION_SIZE; i++) {
    region[i] = i/10.0/3;
  }

  

  for (int i = 0; i < 100000; ++i) {
    auto x = 0.0;
      x += -0.5 * log(rand1.rand());
      x += -0.5 * log(rand2.rand());

    for (int r = 0; r < REGION_SIZE; r++) {
      if (x < region[r]) {
        statistic[r] ++;
        break;
      }
    }
  }

  
  for (int i = 0; i < REGION_SIZE; ++i) {
    std::cout << i/10.0/3 << ", " << statistic[i]  << std::endl;
  }

  
  return 0;
}
