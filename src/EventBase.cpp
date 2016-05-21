#include "EventBase.h"
#include <sstream>

/*
 * Event comparator (for sorting)
 */
std::function<bool (const Event*, const Event*)>
compare =  [] (const Event* a, const Event* b) { 
  return a->occuure_time() > b->occuure_time();
};

std::string Event::get_save_str() const {
  std::ostringstream ss;
  ss << m_type << " " << m_occure_time << "\n";
  return ss.str();
}
