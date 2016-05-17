#include "event_sim.h"

std::string Simulator::save_file_name("save.txt");

std::function<bool (const Event*, const Event*)>
compare =  [] (const Event* a, const Event* b) { 
  return a->occuure_time() > b->occuure_time();
};

void Simulator::run () {
  while (!terminat()) {
    Event * next_event = m_event_queue.top ();
    m_event_queue.pop ();
    m_time = next_event->occuure_time();
    next_event->process();
    delete next_event;
  }
}



