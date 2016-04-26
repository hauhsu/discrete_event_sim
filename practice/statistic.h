#include <vector>
#include <iostream>


std::vector<double> build_region(
    const double low, 
    const double high, 
    const double region_size)
{
  auto num_region = (high-low) / region_size;
  std::vector<double> region(num_region);
  for (int i = 0; i < num_region; i++) {
    region[i] = low + i * region_size;
  }

  return region;
}
/*
std::vector<double> build_region(
    const double region_size, 
    const int num_region, 
    const double middle = 0)
{
  std::vector<double> region(num_region);
  for (int i = 0; i < num_region; i++) {
    region[i] = ((i - num_region/2.0) * region_size + middle);
  }

  return region;
}
*/

std::vector<int> build_distribution(
    std::vector<double> nums, 
    const double low,
    const double high,
    const double region_size)
{
  /*
  std::vector<double> region(num_region);
  for (int i = 0; i < num_region; i++) {
    region[i] = ((i - num_region/2.0) * region_size + middle);
  }
  */

  //auto region = build_region(region_size, num_region);
  
  auto num_region = (high - low) / region_size;
  auto region = build_region(low, high, region_size );

  std::vector<int> distribution(num_region, 0);
  for (int t = 0; t < nums.size(); t++) {
    for (int i = 0; i < num_region; ++i) 
    {
        if (nums[t] < region[i]) {
          distribution[i] ++;
          break;
        }
    }
  }

  return distribution;
}
