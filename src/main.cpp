#include <string>
#include "simple_queue.h"

int main(int argc, char *argv[])
{
  int max_people;
  unsigned int seed;
  if (argc == 4) {
    max_people = std::stoi(argv[1]);
    seed = std::stoi(argv[2]);
    inter_arrival_time_lambda = std::stoi(argv[3]);
  }
  else {
    max_people = 100;
    seed = 10;
  }
  SimpleQueueSim sqs;
  sqs.set_max_people(max_people);
  sqs.set_seed(seed);
  sqs.run();
  std::ofstream seed_file("next_seed.txt");
  seed_file<< sqs.get_seed() << std::endl;
  return 0;
}
