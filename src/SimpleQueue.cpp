#include "SimpleQueue.h"

#include "yaml-cpp/yaml.h"

unsigned Person::m_cnt = 0;


double inter_arrival_time_lambda;

//
// SimpleQueueSim definitions
//
void SimpleQueueSim::gen_arrival_event() {
    auto interarrival_time = m_rand_arrival_time.rand_exp(inter_arrival_time_lambda);
    auto arrival_time = interarrival_time + current_time();
    add_event(new ArriveEvent(arrival_time, *this)); 
}

void SimpleQueueSim::gen_arrival_events(const int num_event) {
  for (int i = 0; i < num_event; ++i) {
    gen_arrival_event();
  }
}


void SimpleQueueSim::serve(Person p) {
  print_time();
  std::cout << "Serving Person " << p.id() << std::endl;
  add_serve_time(p.get_serve_time());
  add_event(new LeaveEvent(current_time()+p.get_serve_time(), *this)); 

}

void SimpleQueueSim::put_in_queue(Person p) {
  print_time();
  std::cout << "Person " << p.id() << " is waiting in queue." << std::endl;
  m_waiting_queue.push(p);

}

void SimpleQueueSim::save_simulation() {

  EventSimulator::save_simulation();
  YAML::Emitter emitter;
  emitter << YAML::BeginDoc;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "service time seed"      << YAML::Value << m_rand_service_time.get_seed();
  emitter << YAML::Key << "interarrival time seed" << YAML::Value << m_rand_arrival_time.get_seed();
  emitter << YAML::Key << "total service time"     << YAML::Value << m_total_service_time;
  emitter << YAML::Key << "max simulaiton people"  << YAML::Value <<  m_max_people;
  emitter << YAML::Key << "simulated people"       << YAML::Value << m_num_simulated_person;
  //People waiting in queue
  emitter << YAML::Key << "waiting queue depth"    << YAML::Value << m_queue_depth;
  emitter << YAML::Key << "number of person instances" << YAML::Value << Person::get_m_cnt();
  emitter << YAML::Key << "people waiting in queue"
          << YAML::BeginSeq;
  for (unsigned i = 0; i < m_waiting_queue.size(); ++i) {
    auto p = m_waiting_queue.front();
    m_waiting_queue.pop();
    m_waiting_queue.push(p);
    p.save(emitter);
  }
  emitter << YAML::EndSeq;
  emitter << YAML::EndDoc;

  std::ofstream save(EventSimulator::save_file_name, std::ios_base::app);
  save << emitter.c_str();
}


void SimpleQueueSim::load_simulation() {

}
