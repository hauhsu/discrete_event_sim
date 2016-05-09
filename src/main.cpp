#include <string>
#include "simple_queue.h"

int main(int argc, char *argv[])
{
  int max_people;
  unsigned int seed;
  if (argc == 4) {
    max_people = std::stoi(argv[1]);
    seed = std::stoi(argv[2]);
    inter_arrival_time_lambda = std::stod(argv[3]);
  }
  else {
    max_people = 100;
    seed = 10;
    inter_arrival_time_lambda = 1;
  }

  std::cout << "Maximum number of simulated people: " << max_people << std::endl;
  std::cout << "Seed: " << seed << std::endl;
  std::cout << "Lambda of inter arrival time: " << inter_arrival_time_lambda<< std::endl;

  SimpleQueueSim sqs;
  sqs.set_max_people(max_people);
  sqs.set_seed(seed);
  sqs.run();
  std::ofstream seed_file("next_seed.txt");
  seed_file<< sqs.get_seed() << std::endl;
  return 0;
}
