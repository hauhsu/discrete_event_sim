#include "event_sim.h"

std::function<bool (const Event*, const Event*)>
compare =  [] (const Event* a, const Event* b) { 
  return a->occuure_time() > b->occuure_time();
};

void Simulator::run () {

  while (! m_event_queue.empty ()) {

    Event * next_event = m_event_queue.top ();
    m_event_queue.pop ();
    m_time = next_event->occuure_time();
    next_event->process();
    delete next_event;
  }
}



