#include <iostream>
#include <vector>
#include <cmath>

#include "PRNG.h"


int main(int argc, char *argv[])
{

  const auto NUM_TEST = 1000;
  const auto alpha = 3.0;

  RandNumGen::RandGen rand_gen(1);
  std::vector<int> statistic(NUM_TEST, 0);

  rand_gen.rand(); 
  for (int test = 0; test < NUM_TEST; test ++){
    auto sum = 0.0;
    for (int i = 0; ;i++){
      auto r = rand_gen.rand();
      auto A = (-1/alpha) * log(r);
      sum += A;
      if (sum  > 1) {
        statistic[test] = i;
        break;
      }
    }
  }

  double avg = 0;

  for (auto t: statistic) {
    std::cout << t << std::endl;
    avg += t;  
  }
  avg /= NUM_TEST;

  std::cout << "Average num of interarrival time: " << avg << std::endl;
  return 0;
}
