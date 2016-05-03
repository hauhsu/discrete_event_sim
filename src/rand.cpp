#include "rand.h"

const int __a = 16807;
const int __m = 2147483647;

unsigned __get_next_seed(unsigned seed)
{
  return  (__a * seed) % __m;
}
