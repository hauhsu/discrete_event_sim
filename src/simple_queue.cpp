#include <queue>
#include <cmath>
#include "event_sim.h"
#include "PRNG.h"

class Person
{
  public:
    Person(): m_id(m_cnt){m_cnt ++;}
    Person(const Person &p): 
      m_id(p.id()), 
      m_serve_time(p.serve_time()){}
    unsigned id() const {return m_id;}

    void set_serve_time(unsigned t) {m_serve_time = t;}
    unsigned serve_time() const {return m_serve_time;}

  private:
    unsigned m_id;
    unsigned m_serve_time;
    static unsigned m_cnt;
    
};

unsigned Person::m_cnt = 0;


class SimpleQueueSim: public Simulator
{
public:
  SimpleQueueSim (unsigned sim_time = 1000, int queue_depth=20): 
    Simulator(sim_time),
    m_queue_depth(queue_depth){
    m_rand_gen2.rand_stream();
    gen_arrival_event(5);
  }

  ~SimpleQueueSim() {
    std::cout << "Total service time: " << m_total_service_time << std::endl;
  }

  void gen_arrival_event(const int num_event)
  {
    std::vector<unsigned> arrival_time_region = {60, 120, 180, 240, 300, 360, 420, 480};
    std::vector<unsigned> arrival_rate = {15, 12, 7, 5, 8, 10, 15, 20, 20};

    for (int i = 0; i < num_event;) {
      unsigned rand = m_rand_gen.rand_exp_distribuiton(5) * 100;
      rand += current_time();

      for (int region = 0; region < arrival_time_region.size(); region++){
        if (rand < arrival_time_region[region]) {
          double ratio = static_cast<double>(5 / arrival_rate[region]);
          auto rand2 = m_rand_gen2.rand();
          if (rand2 < ratio) {
            add_event(new ArriveEvent(rand, *this)); 
            i++;
          }
          break;
        }
      }
    }

  }

  void add_serve_time(unsigned t) {m_total_service_time += t;}

  bool queue_empty() {
    return m_waiting_queue.size() == 0;
  }
  bool queue_full() {
    return m_waiting_queue.size() == m_queue_depth;
  }
  void serve(Person p) {
    print_time();
    std::cout << "Serving Person " << p.id() << std::endl;
    add_serve_time(p.serve_time());
    add_event(new LeaveEvent(current_time()+p.serve_time(), *this)); 
  }

  void put_in_queue(Person p) {
    print_time();
    std::cout << "Person " << p.id() << " is waiting in queue." << std::endl;
    m_waiting_queue.push(p);

  }
  
  class ArriveEvent: public Event
  {
    public:
      ArriveEvent (unsigned t, SimpleQueueSim &s): 
        Event(t), m_parent_sim(s){ std::cout << "Next person will arrive at: " << t << std::endl;}

      void process() override {
        Person p;
        p.set_serve_time(m_parent_sim.m_rand_gen.rand_exp_distribuiton(2)*100);
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
        m_parent_sim.m_waiting_queue.pop();
        m_parent_sim.print_time();
        std::cout << "Person " << p.id() << " is leaving." << std::endl; 
        if (!m_parent_sim.m_waiting_queue.empty()) {
          m_parent_sim.serve(m_parent_sim.m_waiting_queue.front());
        }

        //m_parent_sim.gen_arrival_event(1);
      }
    private:
      SimpleQueueSim& m_parent_sim;
  };

private:
  std::queue<Person> m_waiting_queue;
  unsigned m_queue_depth;
  RandGen m_rand_gen;
  RandGen m_rand_gen2;
  unsigned m_total_service_time;
};

int main(int argc, char *argv[])
{
  SimpleQueueSim sqs;
  sqs.run();
  return 0;
}
