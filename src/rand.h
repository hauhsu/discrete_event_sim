#ifndef RAND_H_H8TP0KED
#define RAND_H_H8TP0KED

#include <iostream>
#include <vector>
#include <cmath>



class Rand
{
  public:
    Rand(int seed=1):
      m_seed(seed) {}

    Rand& operator=(Rand other) {
      m_seed = other.get_seed();
      return *this;
    }
     
    double rand();

    double rand_exp(const double lambda);

    void set_seed(int s) {
      m_seed = s; 
    }

    unsigned get_seed() {
      return m_seed;
    }

    /*
     * Generate a rand stream base on 
     * current seed of the 'this' Rand
     */
    Rand rand_stream();

       
  private:
    unsigned int m_seed;

    static const unsigned __a;
    static const unsigned __m;

    unsigned gen_next_seed() {
      return  (__a * m_seed) % __m;
    }
};






#endif /* end of include guard: RAND_H_H8TP0KED */
