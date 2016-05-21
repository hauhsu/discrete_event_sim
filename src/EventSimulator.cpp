#include "EventSimulator.h"


std::string EventSimulator::save_file_name("save.txt");

EventSimulator::~EventSimulator() {
  while (m_event_queue.size() != 0) {
    delete m_event_queue.top(); 
    m_event_queue.pop();
  }
}


void EventSimulator::run () {
  while (!terminat()) {
    Event * next_event = m_event_queue.top ();
    m_event_queue.pop ();
    m_time = next_event->occuure_time();
    next_event->process();
    delete next_event;
  }
}


void EventSimulator::save_simulation() {
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


void EventSimulator::load_simulation() {

}
