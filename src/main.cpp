#include <string>
#include "SimpleQueue.h"

int main(int argc, char *argv[])
{
  auto max_people = 5;
  unsigned seed = 10;
  auto interarrival_time_mean = 11.0;

  if (argc == 4) {
    max_people = std::stoi(argv[1]);
    seed = std::stoi(argv[2]);
    interarrival_time_mean = std::stod(argv[3]);
  }

  std::cout << "--------------------------------------" << std::endl;
  std::cout << "Maximum number of simulated people: " << max_people << std::endl;
  std::cout << "Seed: " << seed << std::endl;
  std::cout << "Mean of inter-arrival time: " << interarrival_time_mean << std::endl;
  std::cout << "--------------------------------------\n" << std::endl;

  inter_arrival_time_lambda = 1.0 / interarrival_time_mean;
  SimpleQueueSim sqs;
  sqs.set_max_people(max_people);
  sqs.set_seed(seed);
  sqs.run();
  sqs.save_simulation();
  std::ofstream seed_file("next_seed.txt");
  seed_file<< sqs.get_seed() << std::endl;
  sqs.load_simulation();
  sqs.save_simulation("re_save.yaml");
  return 0;
}
