#include <queue>
#include "event_sim.h"
#include "PRNG.h"

struct Person
{
  public:
    int id;
};

class ArriveEvent: public Event
{
public:
  ArriveEvent (unsigned t): Event(t){}

  void process() override {
       
  }

private:
};

class SimpleQueueSim: public Simulator
{
public:
  SimpleQueueSim (int queue_size);

  bool queue_has_space();
  

private:
  std::queue<Person> m_waiting_queue;
};
