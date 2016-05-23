#include "EventSimulator.h"
#include "yaml-cpp/yaml.h"


std::string EventSimulator::save_file_name("save.yaml");

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


void EventSimulator::save_simulation(std::string save_file) {
  YAML::Emitter emitter;
  emitter << YAML::BeginDoc;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "time" << YAML::Value << m_time;
  emitter << YAML::Key << "max simulation time" << YAML::Value << m_max_sim_time ;

  emitter << YAML::Key << "events" << YAML::Value;
  emitter << YAML::BeginSeq;
  auto q_size = m_event_queue.size();
  //pop events from priority queue and put into a vector
  std::vector<Event*> tmp;
  for (unsigned i = 0;  i < q_size; i++) {
    auto next_event = m_event_queue.top();
    m_event_queue.pop();
    tmp.push_back(next_event);
  }
  //save and put event back from vector
  for (auto &event : tmp) {
    event->save(emitter);
    m_event_queue.push(event);
  }
  emitter << YAML::EndSeq;
  emitter << YAML::EndMap;
  emitter << YAML::EndDoc;

  std::ofstream save(save_file);
  save << emitter.c_str();

}


void EventSimulator::load_simulation(std::string load_file) {
  YAML::Node saved = YAML::LoadFile(load_file);
  m_time = saved["time"].as<Time>();
  m_max_sim_time = saved["max simulation time"].as<Time>();
  std::cout << "m_time: " << m_time << std::endl;
}
