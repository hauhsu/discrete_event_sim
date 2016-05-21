#include "event_sim.h"

Simulator::~Simulator() {
  while (m_event_queue.size() != 0) {
    delete m_event_queue.top(); 
    m_event_queue.pop();
  }
}

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


void Simulator::save_simulation() {
  std::ofstream save("save.txt");
  save << m_time << std::endl;
  save << m_max_sim_time << std::endl;
  save << m_event_queue.size() << std::endl;

  auto q_size = m_event_queue.size();
  //pop events from priority queue and put into a vector
  std::vector<Event*> tmp;
  for (int i = 0;  i < q_size; i++) {
    auto next_event = m_event_queue.top();
    m_event_queue.pop();
    tmp.push_back(next_event);
    std::cout << next_event->get_save_str();
  }
  //save put event back from vector
  for (auto &event : tmp) {
    save << event->get_save_str();
    m_event_queue.push(event);
  }
 
}



