#pragma once

#include <queue>
#include <cmath>
#include <fstream>
#include <iostream>
#include <cassert>

#include "yaml-cpp/yaml.h"

#include "rand.h"
#include "EventSimulator.h"

class Person
{
  public:
    Person(): 
      m_id(m_cnt),
      m_serve_time(0),
      m_arrival_time(0),
      m_leave_time(0)
    {m_cnt ++;}

    Person(
        unsigned id,
        Time arrival_time, 
        Time service_time, 
        Time leave_time): 
      m_id(id),
      m_serve_time(service_time),
      m_arrival_time(arrival_time),
      m_leave_time(leave_time)
    {}
    
    Person(const Person &p): 
      m_id( p.id() ), 
      m_serve_time( p.get_serve_time() ),
      m_arrival_time( p.get_arrival_time() ),
      m_leave_time( p.get_leave_time() )
    {}

    unsigned id() const {
      return m_id;
    }

    void set_serve_time(const Time t) {
      m_serve_time = t;
    }

    double get_serve_time() const {
      return m_serve_time;
    }

    void set_arrival_time(const Time time) {
      m_arrival_time = time;
    }

    Time get_arrival_time() const {
      return m_arrival_time;
    }

    void set_leave_time(const Time time) {
      m_leave_time= time;
    }

    Time get_leave_time() const {
      return m_leave_time;
    }

    Time get_system_time() const {
      return m_leave_time - m_arrival_time;
    }

    void save(YAML::Emitter& emitter) const {
      emitter << YAML::BeginMap;
      emitter << YAML::Key << "id" << YAML::Value << m_id;
      emitter << YAML::Key << "service time" << YAML::Value << m_serve_time;
      emitter << YAML::Key << "arrival time" << YAML::Value << m_arrival_time;
      emitter << YAML::Key << "leave time"   << YAML::Value << m_leave_time;
      emitter << YAML::EndMap;
    }

    static unsigned get_cnt() {return m_cnt;}
    static void set_cnt(unsigned cnt) {m_cnt = cnt;}

  private:
    unsigned m_id;
    Time m_serve_time;
    static unsigned m_cnt;

    //duration in the system (waiting time + service time)
    Time m_arrival_time;
    Time m_leave_time;
    
};

class SimpleQueueSim: public EventSimulator
{
  public:
    SimpleQueueSim (): 
      EventSimulator(),
      m_queue_depth(1000)
  {
    person_sys_time.open("person_sys_time.txt");
  }

  ~SimpleQueueSim() {
    std::cout << "Total service time: " << m_total_service_time << std::endl;
    person_sys_time.close();
  }

  void set_max_sim_time(Time t) {
    EventSimulator::set_max_sim_time(t);
  }

  void set_queue_depth(unsigned d) {
    m_queue_depth = d;
  }

  void set_max_people(unsigned num) {
    m_max_people = num;
  }

  void set_seed(unsigned seed) {
    m_rand_arrival_time.set_seed(seed);
    m_rand_service_time = m_rand_arrival_time.rand_stream();
  }

  void set_interarrival_rand_seed(unsigned seed) {
    m_rand_arrival_time.set_seed(seed);
  }

  void set_service_rand_seed(unsigned seed) {
    m_rand_service_time.set_seed(seed);
  }

  void set_interarrival_lambda(const double lambda) {
    m_inter_arrival_time_lambda = lambda; 
  }

  unsigned get_seed() {
    return m_rand_arrival_time.get_seed();
  }

  virtual void run() override {
    gen_arrival_event();
    EventSimulator::run();
  }

  virtual bool terminat() override{
    return EventSimulator::terminat() or  m_num_simulated_person >= m_max_people;
  }


  void gen_arrival_event();
  void gen_arrival_events(const int num_events);

  void add_serve_time(Time t) {m_total_service_time += t;}


  bool queue_empty() {
    return m_waiting_queue.size() == 0;
  }
  bool queue_full() {
    return m_waiting_queue.size() == m_queue_depth;
  }

  void serve(Person p);

  void put_in_queue(Person p);
  
  virtual void 
    save_simulation(std::string save_file=EventSimulator::save_file_name) override ;
  virtual void 
    load_simulation(std::string load_file=EventSimulator::save_file_name) override ;

private:
  class ArriveEvent;
  class LeaveEvent;
  Event* event_factory(const std::string type, const Time occuure_time);
  std::queue<Person> m_waiting_queue;
  unsigned m_queue_depth;
  Rand m_rand_arrival_time;
  Rand m_rand_service_time;
  Time m_total_service_time;
  unsigned m_max_people;
  unsigned m_num_simulated_person;
  Time m_inter_arrival_time_lambda;

  std::ofstream person_sys_time;
};


class SimpleQueueSim::ArriveEvent: public Event
{
  public:
    ArriveEvent (Time t, SimpleQueueSim &s): 
      Event(t, "ArriveEvent"), 
      m_parent_sim(s) 
  { 
    std::cout << "Next person will arrive at: " << t << std::endl;
  }

    void process() override {
      Person p;
      p.set_arrival_time( m_parent_sim.current_time() );
      p.set_serve_time( m_parent_sim.m_rand_service_time.rand_exp(1.0/10) );
      if (m_parent_sim.queue_empty()) {
        m_parent_sim.m_waiting_queue.push(p);
        m_parent_sim.serve(p);
      }

      else if (m_parent_sim.queue_full()) {
        m_parent_sim.print_time();
        std::cout << "Queue is full!!!\n";
        assert(0);
      }

      else {
        m_parent_sim.put_in_queue(p);
      }
      m_parent_sim.gen_arrival_event();
    }
  private:
    SimpleQueueSim& m_parent_sim;
};

class SimpleQueueSim::LeaveEvent: public Event
{
  public:
    LeaveEvent(Time t, SimpleQueueSim &s): 
      Event(t, "LeaveEvent"), m_parent_sim(s){
        std::cout << "Service time is " << t-m_parent_sim.current_time() << std::endl; 
      }

    void process() override {
      Person p = m_parent_sim.m_waiting_queue.front();
      p.set_leave_time( m_parent_sim.current_time() );
      m_parent_sim.m_waiting_queue.pop();
      m_parent_sim.print_time();
      std::cout << "Person " << p.id() << " is leaving." << std::endl; 
      if (!m_parent_sim.m_waiting_queue.empty()) {
        m_parent_sim.serve(m_parent_sim.m_waiting_queue.front());
      }

      m_parent_sim.person_sys_time << p.get_system_time() << std::endl;
      m_parent_sim.m_num_simulated_person++;
    }
  private:
    SimpleQueueSim& m_parent_sim;
};

