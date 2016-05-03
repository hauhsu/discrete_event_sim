#pragma once

#include <queue>
#include <cmath>
#include <fstream>
#include <iostream>

#include "rand.h"
#include "event_sim.h"

class Person
{
  public:
    Person(): m_id(m_cnt){m_cnt ++;}
    Person(const Person &p): 
      m_id( p.id() ), 
      m_serve_time( p.get_serve_time() ),
      m_arrival_time( p.get_arrival_time() ),
      m_leave_time( p.get_leave_time() )
      {}

    unsigned id() const {
      return m_id;
    }

    void set_serve_time(unsigned t) {
      m_serve_time = t;
    }

    unsigned get_serve_time() const {
      return m_serve_time;
    }

    void set_arrival_time(unsigned time) {
      m_arrival_time = time;
    }

    void set_leave_time(unsigned time) {
      m_leave_time= time;
    }

    unsigned get_arrival_time() const {
      return m_arrival_time;
    }

    unsigned get_leave_time() const {
      return m_leave_time;
    }

    unsigned get_system_time() const {
      return m_leave_time - m_arrival_time;
    }

  private:
    unsigned m_id;
    unsigned m_serve_time;
    static unsigned m_cnt;

    //duration in the system (waiting time + service time)
    unsigned m_arrival_time;
    unsigned m_leave_time;
    
};



class SimpleQueueSim: public Simulator
{
public:
  SimpleQueueSim (unsigned sim_time = 1000, int queue_depth=20): 
    Simulator(sim_time),
    m_queue_depth(queue_depth){
    gen_arrival_event(5);

    person_sys_time.open("person_sys_time.txt");
  }

  ~SimpleQueueSim() {
    std::cout << "Total service time: " << m_total_service_time << std::endl;
    person_sys_time.close();
  }

  
  void set_max_people(unsigned num) {
    m_max_people = num;
  }

  void set_seed(unsigned seed) {
    m_rand_arrival_time.seed(seed);
  }


  virtual bool terminat() {
    return Simulator::terminat() or  m_num_simulated_person >= m_max_people;
  }


  void gen_arrival_event(const int num_event);

  void add_serve_time(unsigned t) {m_total_service_time += t;}


  bool queue_empty() {
    return m_waiting_queue.size() == 0;
  }
  bool queue_full() {
    return m_waiting_queue.size() == m_queue_depth;
  }

  void serve(Person p);

  void put_in_queue(Person p);
  
  class ArriveEvent: public Event
  {
    public:
      ArriveEvent (unsigned t, SimpleQueueSim &s): 
        Event(t), m_parent_sim(s){ std::cout << "Next person will arrive at: " << t << std::endl;}

      void process() override {
        Person p;
        p.set_arrival_time( m_parent_sim.current_time() );
        p.set_serve_time( m_parent_sim.m_rand_arrival_time.rand_exp_distribuiton(2)*100 );
        if (m_parent_sim.queue_empty()) {
          m_parent_sim.m_waiting_queue.push(p);
          m_parent_sim.serve(p);
        }

        else if (m_parent_sim.queue_full()) {
          m_parent_sim.print_time();
          std::cout << "Queue is full!!!\n";
        }

        else {
          m_parent_sim.put_in_queue(p);
        }

      }
    private:
      SimpleQueueSim& m_parent_sim;
  };

  class LeaveEvent: public Event
  {
    public:
      LeaveEvent(unsigned t, SimpleQueueSim &s): 
        Event(t), m_parent_sim(s){
          std::cout << "Service time is " << t << std::endl; 
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

        m_parent_sim.gen_arrival_event(1);

        m_parent_sim.person_sys_time << p.get_system_time() << std::endl;
        m_parent_sim.m_num_simulated_person++;
      }
    private:
      SimpleQueueSim& m_parent_sim;
  };

private:
  std::queue<Person> m_waiting_queue;
  unsigned m_queue_depth;
  RandGen m_rand_arrival_time;
  unsigned m_total_service_time;
  unsigned m_max_people;
  unsigned m_num_simulated_person;

  std::ofstream person_sys_time;

};