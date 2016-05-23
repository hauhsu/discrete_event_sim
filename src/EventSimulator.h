#pragma once
#include <queue>
#include <sstream>
#include <functional>
#include <iostream>
#include <fstream>
#include "EventBase.h"

extern 
std::function<bool (const Event*, const Event*)> compare;

class EventSimulator
{
public:
  EventSimulator (): 
    m_time(0), 
    m_max_sim_time(100000),
    m_event_queue(compare)
  {}

  virtual ~EventSimulator ();

  void set_max_sim_time(Time t) {
    m_max_sim_time = t;
  }

  void run();

  virtual bool terminat() {
    return (m_event_queue.empty()) or (m_time > m_max_sim_time);
  }

  void add_event(Event *new_event) {
    m_event_queue.push(new_event);  
  }

  Time current_time() {
    return m_time;
  }

  void print_time() {
    std::cout << "\n"
              << "--- @" << m_time << " --- \n";
  }


  /*
   * Save/load simulation
   */
  static std::string save_file_name;
  virtual void save_simulation(std::string save_file=save_file_name);
  virtual void load_simulation(std::string load_file=save_file_name);

private:
  Time m_time;
  Time m_max_sim_time;
  
  std::priority_queue
    <Event*, 
     std::vector<Event*>, 
     decltype(compare)> m_event_queue;
};
