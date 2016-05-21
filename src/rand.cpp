#include "rand.h"

const unsigned Rand::__a(16807);
const unsigned Rand::__m(2147483647);

double Rand::rand(){ 
  m_seed = gen_next_seed();
  return static_cast<double>(m_seed)  / __m;
}

double Rand::rand_exp(const double lambda) {
  double r = rand();
  return  (-1.0/lambda) * log(1 - r);
}

Rand Rand::rand_stream() {
  //Just copy a Rand instance and 
  //jump many times then return it
  Rand r(this->m_seed);
  auto interval = 1000000;

  for (int i = 0; i < interval; ++i) {
    r.rand();
  }
  return r;
}

