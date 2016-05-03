#pragma once
#include <queue>
#include <functional>
#include <iostream>

class Event
{
public:
  Event (unsigned t): m_occure_time(t){
  }
  virtual ~Event (){}

  virtual void process() = 0;
  unsigned occuure_time() const {return m_occure_time;}

private:
  unsigned m_occure_time;

};
extern 
std::function<bool (const Event*, const Event*)> compare;

class Simulator
{
public:
  Simulator (unsigned sim_time): 
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
    std::cout << " --- " << m_time << " --- \n";
  }

  unsigned current_time() {
    return m_time;
  }

private:
  unsigned m_time;
  unsigned m_max_sim_time;
  
  std::priority_queue
    <Event*, 
     std::vector<Event*>, 
     decltype(compare)> m_event_queue;

};
