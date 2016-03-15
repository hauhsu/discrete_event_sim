#include "../src/PRNG.h"

using namespace RandNumGen;


int main(int argc, char *argv[])
{

  RandGen rand_gen;
  RandGen rand_gen2;
  rand_gen.rand_stream();
  rand_gen2.rand_stream();

  std::cout << "rand gen 1 init seed: " << rand_gen.get_seed() << std::endl;
  std::cout << "rand gen 2 init seed: " << rand_gen2.get_seed() << std::endl;

  std::vector<double> rand_nums;
  /*
  for (int i=0; i<5; i++) {
    double r = rand_gen.rand();
    rand_nums.push_back(r);
  }

  std::cout << std::endl;
  std::cout << "D-alfa = " << Kolmogorov_Smirnov_test(rand_nums) << std::endl;
  */

  rand_gen.rand();
  for (int i=0; i<10; i++) {
    double r = rand_gen.rand();
    rand_nums.push_back(r);
    std::cout << r << std::endl;
  }
  std::cout << std::endl;
  //double X0 = chi_square_test(rand_nums) ;
  //std::cout << "X0 = " << X0 << std::endl;
  //
  double Z0 = autocorrelation_test(rand_nums, 1, 2);
  std::cout << "Z0 = " << Z0 << std::endl;

  double Ai = rand_gen.rand_exp_distribuiton(2);
  double Si = rand_gen.rand_exp_distribuiton(3);

  std::cout << "Ai = " << Ai << std::endl;
  std::cout << "Si = " << Si << std::endl;
  
  return 0;
}


