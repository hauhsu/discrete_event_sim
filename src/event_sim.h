#pragma once
#include <queue>
#include <sstream>
#include <functional>
#include <iostream>
#include <fstream>

using Time = double;


class Event
{
public:
  Event (Time t, std::string type): 
    m_occure_time(t),
    m_type(type)
  {}
  virtual ~Event (){}

  virtual void process() = 0;
  std::string get_save_str() const {
    std::ostringstream ss;
    ss << m_type << " " << m_occure_time << "\n";
    return ss.str();
  }
  Time occuure_time() const {return m_occure_time;}
  std::string type() const {return m_type;}

private:
  Time m_occure_time;
  std::string m_type;
};
extern 
std::function<bool (const Event*, const Event*)> compare;

class Simulator
{
public:
  Simulator (Time max_sim_time): 
    m_time(0), 
    m_max_sim_time(max_sim_time),
    m_event_queue(compare)
  {}

  virtual ~Simulator ();

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


  virtual void save_simulation();
  void load_simulation();

  static std::string save_file_name;
private:
  Time m_time;
  Time m_max_sim_time;
  
  std::priority_queue
    <Event*, 
     std::vector<Event*>, 
     decltype(compare)> m_event_queue;
};
