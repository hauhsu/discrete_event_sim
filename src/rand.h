#ifndef RAND_H_H8TP0KED
#define RAND_H_H8TP0KED



#include <iostream>
#include <vector>
#include <cmath>


extern const int __a;
extern const int __m;

unsigned __get_next_seed(unsigned seed);

class RandGen
{
  public:
    RandGen(int seed=1): m_seed(seed){}
     
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
       
  private:
    unsigned int m_seed;
};

class RandStream
{
  public:
    RandStream(int seed = 1, int interval = 1000000):
      m_next_init_seed(seed), m_interval(interval){}

    void set_seed_interval(int interval) {
        m_interval = interval;
    }

    void set_seed(unsigned seed) {
      m_next_init_seed = seed;
    }

    unsigned get_seed() {
      return m_next_init_seed;
    }

    RandGen get_rand_gen() {
      auto r = RandGen(m_next_init_seed); 
      get_next_seed();
      return r;
    }

    static RandStream& instance() {
      static RandStream s_instance;
        return s_instance;
    }

  private:
    unsigned get_next_seed() {
        for (int i = 0; i < m_interval; ++i) {
          m_next_init_seed = __get_next_seed(m_next_init_seed);
        }
        return m_next_init_seed;
    }



    //Disable copy methods
    RandStream(RandStream &s) = delete;
    void operator = (RandStream const&) = delete;

  private: 
    unsigned m_next_init_seed;
    int m_interval;

};





#endif /* end of include guard: RAND_H_H8TP0KED */
