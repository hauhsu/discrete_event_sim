#pragma once
#include <queue>
#include <functional>
#include <iostream>

using Time = double;


class Event
{
public:
  Event (Time t): m_occure_time(t){
  }
  virtual ~Event (){}

  virtual void process() = 0;
  Time occuure_time() const {return m_occure_time;}

private:
  Time m_occure_time;

};
extern 
std::function<bool (const Event*, const Event*)> compare;

class Simulator
{
public:
  Simulator (Time sim_time): 
    m_time(0), 
    m_max_sim_time(sim_time),
    m_event_queue(compare)
  {}

  virtual ~Simulator () {}

  void run();

  virtual bool terminat() {
    return (m_event_queue.empty()) or (m_time > m_max_sim_time);
  }

  void add_event(Event *new_event) {

    m_event_queue.push(new_event);  
  }
  void print_time() {
    std::cout << "\n"
              << "--- @" << m_time << " --- \n";
  }

  Time current_time() {
    return m_time;
  }

private:
  Time m_time;
  Time m_max_sim_time;
  
  std::priority_queue
    <Event*, 
     std::vector<Event*>, 
     decltype(compare)> m_event_queue;

};
