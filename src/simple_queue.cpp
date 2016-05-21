#include "simple_queue.h"

unsigned Person::m_cnt = 0;


double inter_arrival_time_lambda;

//
// SimpleQueueSim definitions
//
void SimpleQueueSim::gen_arrival_event(const int num_event)
{
  for (int i = 0; i < num_event; ++i) {
    double arrival_time = m_rand_arrival_time.rand_exp(inter_arrival_time_lambda) + current_time();
    add_event(new ArriveEvent(arrival_time, *this)); 
  }
}


void SimpleQueueSim::serve(Person p) {
  print_time();
  std::cout << "Serving Person " << p.id() << std::endl;
  add_serve_time(p.get_serve_time());
  add_event(new LeaveEvent(current_time()+p.get_serve_time(), *this)); 

}

void SimpleQueueSim::put_in_queue(Person p) {
  print_time();
  std::cout << "Person " << p.id() << " is waiting in queue." << std::endl;
  m_waiting_queue.push(p);

}

