#include <iostream>
#include <vector>
#include "PRNG.h"

int main(int argc, char *argv[])
{
  const int k = 2;
  std::vector<RandNumGen::RandGen> rand(k);
  for (auto &r : rand) {
    r.rand_stream();
  }
  

  /*
  const int REGION_SIZE = 100;
  std::vector<int> statistic(REGION_SIZE, 0);
  std::vector<double> region(REGION_SIZE);
  */

  

  for (int i = 0; i < 10; ++i) {
    auto x = 0.0;
    for (int j = 0; j < k; j++){
      std::cout << rand[k].rand() << std::endl;
      x += -0.5 * log(rand[k].rand());
      std::cout << x << std::endl;
    }
  }
  
  return 0;
}
