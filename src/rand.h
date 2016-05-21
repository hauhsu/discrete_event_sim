#ifndef RAND_H_H8TP0KED
#define RAND_H_H8TP0KED

#include <iostream>
#include <vector>
#include <cmath>



class RandGen
{
  public:
    RandGen(int seed=1):
      m_seed(seed),
      __a(16807),
      __m(2147483647)
    {}


    RandGen& operator=(RandGen other) {
      m_seed = other.get_seed();
      return *this;
    }
     
    double rand(){ 
      m_seed = __get_next_seed(m_seed);
      return static_cast<double>(m_seed)  / __m;
    }

    double rand_exp_distribuiton(const double lambda) {
      double r = rand();
      return  (-1.0/lambda) * log(1 - r);
    }

    void seed(int s) {
      m_seed = s; 
    }

    unsigned get_seed() {
      return m_seed;
    }

    /*
     * Generate a rand stream base on 
     * current seed of the RandGen
     */
    RandGen rand_stream() {
      RandGen r(m_seed);
      auto interval = 1000000;

      for (int i = 0; i < interval; ++i) {
        r.seed(__get_next_seed(r.get_seed()));
      }
      return r;
    }

       
  private:
    unsigned int m_seed;

    const int __a;
    const int __m;

    unsigned __get_next_seed(unsigned seed)
    {
      return  (__a * seed) % __m;
    }
};






#endif /* end of include guard: RAND_H_H8TP0KED */
