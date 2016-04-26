#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
  std::vector<double> v1 = 
        {99.55, 99.56, 99.62, 99.65, 99.79, 
         99.98, 100.02, 100.06, 100.17, 100.23,
        100.26, 100.27, 100.33, 100.41, 100.47};

  auto mean = 99.99;
  auto variance = 0.2832; 

  for (int i = 0; i < v1.size(); ++i) {
    std::cout << v1[i] << ", " << mean + variance*( (i-0.5) / v1.size() ) << std::endl;
  }
  
  return 0;
}
