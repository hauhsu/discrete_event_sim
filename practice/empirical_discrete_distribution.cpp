#include <iostream>
#include <cmath>
#include <vector>
#include "PRNG.h"

using namespace std;

int main(int argc, char *argv[])
{
  vector<double> p1 = {0.5, 0.8, 1};
  vector<int> statistic(3, 0);
  RandNumGen::RandGen rand_gen;
  
  const int NUM_SAMPLE = 1000;
  for (int i = 0; i < NUM_SAMPLE; i++) {
    auto r = rand_gen.rand();
    for (int j = 0; j < p1.size(); j++) {
      if (r < p1[j]) {
        statistic[j]++;
        break;
      }
    }
  }

  for (auto s: statistic) {
    cout << static_cast<double>(s) / NUM_SAMPLE << endl;
  }

  const int region = 10;
  vector<double> p2(region, 0);
  vector<int> statistic2(region, 0);
  for (int i = 0; i < region; ++i) {
    p2[i] = (i+1);
  }

  cout << endl;

  const double p = 0.5;
  for (int i = 0; i < NUM_SAMPLE; i++) {
    auto r = rand_gen.rand();
    auto X = abs(ceil( log(1-r)/log(1-p) - 1 ));

    for (int j = 0; j < p2.size(); j++) {
      if (X < p2[j]) {
        statistic2[j]++;
        break;
      }
    }
  }

  cout << "Statistic 2" << endl;
  for (auto s: statistic2) {
    cout << static_cast<double>(s) / NUM_SAMPLE << endl;
  }

  return 0;
}
