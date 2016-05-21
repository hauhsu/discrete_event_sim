#include "EventBase.h"
#include <sstream>

std::string Event::get_save_str() const {
  std::ostringstream ss;
  ss << m_type << " " << m_occure_time << "\n";
  return ss.str();
}
