
#include "simple_queue.h"

int main(int argc, char *argv[])
{
  SimpleQueueSim sqs;
  sqs.set_max_people(10);
  sqs.run();
  return 0;
}
