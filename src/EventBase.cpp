#include "EventBase.h"
#include <sstream>

/*
 * Event comparator (for sorting)
 */
std::function<bool (const Event*, const Event*)>
compare =  [] (const Event* a, const Event* b) { 
  return a->occuure_time() > b->occuure_time();
};

void Event::save(YAML::Emitter &emitter) const {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "type" << YAML::Value << m_type;
  emitter << YAML::Key << "occure time" << YAML::Value << m_occure_time;
  emitter << YAML::EndMap;
}
