#ifndef RAND_H_H8TP0KED
#define RAND_H_H8TP0KED



#include <iostream>
#include <vector>
#include <cmath>


extern const int __a;
extern const int __m;

unsigned __get_next_seed(unsigned seed);

class __RandStream
{
  public:
    __RandStream(int seed = 1, int interval = 1000000):
      m_next_init_seed(seed), m_interval(interval){}

    unsigned get_next_seed() {
        for (int i = 0; i < m_interval; ++i) {
          m_next_init_seed = __get_next_seed(m_next_init_seed);
        }
        return m_next_init_seed;
    }

    void set_seed_interval(int interval) {
        m_interval = interval;
    }

    static __RandStream& instance() {
      static __RandStream s_instance;
        return s_instance;
    }

    //Disable copy methods
    __RandStream(__RandStream &s) = delete;
    void operator = (__RandStream const&) = delete;

  private: 
    unsigned m_next_init_seed;
    int m_interval;

};

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

    void rand_stream() {
      m_seed = __RandStream::instance().get_next_seed();
    }

    unsigned get_seed() {
      return m_seed;
    }
       
  private:
    unsigned int m_seed;
};




#endif /* end of include guard: RAND_H_H8TP0KED */
