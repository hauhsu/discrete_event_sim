#include <vector>
#include <iostream>
#include "PRNG.h"

double empriical_cont_distribution(double r)
{
  std::vector<double> c = {0.31, 0.41, 0.66, 1.0};
  std::vector<double> a = {0.81, 5.0, 2.0, 1.47};

  double idx = 0;
  for (auto Ci : c) {
    if (r > Ci) idx ++ ;
    else break;
  }
   
  return  0.5*idx + a[idx]*(r - c[idx-1]);
}


int main(int argc, char *argv[])
{
  
  std::cout <<  empriical_cont_distribution(0.83)<< std::endl;
  RandNumGen::RandGen rand_gen;

  std::vector<double> c = {0.31, 0.41, 0.66, 1.0};
  std::vector<int> counter(4, 0);

  const int TEST_NUM = 10000;
  for (int i=0; i< TEST_NUM; i++){
    double r = rand_gen.rand();

    for (int idx = 0; idx < 4; idx ++) {
      if (r > c[idx]) continue;
      else {
        counter[idx]++;
        break;
      }
    }
  }
  std::cout << std::endl;

  for (int i=0; i<4; i++) {
    std::cout << static_cast<double>(counter[i])/TEST_NUM << std::endl;
  }

  return 0;
}
