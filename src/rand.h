#include <iostream>
#include <vector>
#include <cmath>


const int __a = 16807;
const int __m = 2147483647;

unsigned __rand(unsigned seed)
{
  return  (__a * seed) % __m;
}

class __RandStream
{
  public:
    __RandStream(int s = 1, int interval = 1000000):
      m_next_init_seed(s), m_interval(interval){}

    unsigned get_next_seed() {
        for (int i = 0; i < m_interval; ++i) {
          m_next_init_seed = __rand(m_next_init_seed);
        }
        return m_next_init_seed;
    }

    void set_seed_interval(int v) {
        m_interval = v;
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
      //return a rand num between 0 and 1
      m_seed = __rand(m_seed);

      return static_cast<double>(m_seed)  / __m;
    }

    double rand_exp_distribuiton(const double lambda) {
      double r = rand();
      //std::cout << r << std::endl;
      return  (-1/lambda) * log(1 - r);
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



double Kolmogorov_Smirnov_test(std::vector<double> rand_nums)
{
  std::vector<double> Rn;
  Rn.push_back(0);
  for (int i = rand_nums.size(); i > 0; i--) {
    Rn.push_back(1.0/i);
  }

  std::sort (rand_nums.begin(), rand_nums.end());
  double max = 0;
  for (int i = 0; i < rand_nums.size(); i++) {
    double diff = std::abs(rand_nums[i] - Rn[i]);
    if ( diff > max) {
      max = diff;
    }
  }
  for (int i = 0; i < rand_nums.size(); i++) {
    if ( (rand_nums[i] - Rn[i+1]) > max) {
      max = rand_nums[i]-Rn[i+1];
    }
  }
  
  return max;
}

double chi_square_test(std::vector<double> rand_nums)
{
  const int n  = 10; //number of classes
  int N  = rand_nums.size(); //numver of observations
  int Ei = N/n; //expected num in class

  double a = 1.0/n; //distance between classes

  std::vector<double> classes;
  for (int i = 0; i<n; i++ ) classes.push_back(0);

  for (auto i: rand_nums){
    classes[int(i/a)] ++;
  }
  double X0 = 0;
  for (auto Oi: classes) {
    X0 += ( (Ei - Oi) * (Ei - Oi) ) / double(Ei);
  }

  return X0;
}

double autocorrelation_test(std::vector<double> rand_nums, const int i, const int m)
{
  const int N = rand_nums.size();
  const int M = (static_cast<double>(N)-i)/m - 1.0;
  std::cout << "i = " << i << std::endl;
  std::cout << "m = " << m << std::endl;
  std::cout << "N = " << N << std::endl;
  std::cout << "M = " << M << std::endl;
  double mul_sum = 0;
  for (int Ri = i; Ri < N-1; Ri+=m) {
    std::cout << rand_nums[Ri] << ", " << rand_nums[Ri+m] << std::endl;
    mul_sum += rand_nums[Ri]*rand_nums[Ri+m]; 
  }
  double lo = mul_sum/(M+1.0) - 0.25;
  double pyi = pow((13*M + 7), 0.5) / (12*(M+1));
  std::cout << "lo = " << lo << std::endl;
  std::cout << "pyi = " << pyi << std::endl;
  double Z0 = lo / pyi;

  return Z0;
}

