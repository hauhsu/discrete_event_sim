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


void SimpleQueueSim::save_simulation(std::string save_file) {

  EventSimulator::save_simulation(save_file);
  YAML::Emitter emitter;
  emitter << YAML::BeginDoc;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "service time seed"      << YAML::Value << m_rand_service_time.get_seed();
  emitter << YAML::Key << "interarrival time seed" << YAML::Value << m_rand_arrival_time.get_seed();
  emitter << YAML::Key << "total service time"     << YAML::Value << m_total_service_time;
  emitter << YAML::Key << "max simulation people"  << YAML::Value <<  m_max_people;
  emitter << YAML::Key << "simulated people"       << YAML::Value << m_num_simulated_person;
  //People waiting in queue
  emitter << YAML::Key << "waiting queue depth"    << YAML::Value << m_queue_depth;
  emitter << YAML::Key << "number of person instances" << YAML::Value << Person::get_cnt();
  emitter << YAML::Key << "people waiting in queue" << YAML::Value;
  emitter << YAML::BeginSeq;
  for (unsigned i = 0; i < m_waiting_queue.size(); ++i) {
    auto p = m_waiting_queue.front();
    m_waiting_queue.pop();
    m_waiting_queue.push(p);
    p.save(emitter);
  }
  emitter << YAML::EndSeq;
  emitter << YAML::EndMap;
  emitter << YAML::EndDoc;

  std::ofstream save(save_file, std::ios_base::app);
  save << emitter.c_str();
}

Event* SimpleQueueSim::event_factory(const std::string type, Time const occuure_time) {
  if (type == "LeaveEvent") return new LeaveEvent(occuure_time, *this);
  else if (type == "ArriveEvent") return new ArriveEvent(occuure_time, *this);
  assert(false);
  return NULL;
}


void SimpleQueueSim::load_simulation() {
  std::ifstream fin(EventSimulator::save_file_name);
  auto saved_all = YAML::LoadAllFromFile(EventSimulator::save_file_name);

  auto saved = saved_all[0];
  for (size_t i = 0; i < saved["events"].size(); ++i) {
    auto event = event_factory(saved["events"][i]["type"].as<std::string>(),  
                               saved["events"][i]["occure time"].as<Time>());
    add_event(event);
  }

  saved = saved_all[1];
  m_rand_service_time.set_seed(saved["service time seed"].as<unsigned>());
  m_rand_arrival_time.set_seed(saved["interarrival time seed"].as<unsigned>());
  m_total_service_time = saved["total service time"].as<Time>();
  m_max_people = saved["max simulation people"].as<unsigned>();
  m_num_simulated_person = saved["simulated people"].as<unsigned>();
  m_queue_depth = saved["waiting queue depth"].as<unsigned>();
  Person::set_cnt(saved["number of person instances"].as<unsigned>());
  for (size_t i = 0; i < saved["people waiting in queue"].size(); ++i) {
    auto id = saved["people waiting in queue"][i]["id"].as<unsigned>();
    auto arrival_time = saved["people waiting in queue"][i]["arrival time"].as<Time>();
    auto service_time = saved["people waiting in queue"][i]["service time"].as<Time>();
    auto leave_time =   saved["people waiting in queue"][i]["leave time"].as<Time>();
  
    auto p = Person(id, arrival_time, service_time, leave_time);
    m_waiting_queue.push(p);
  }

}
