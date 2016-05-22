#pragma once
#include <string>
#include "yaml-cpp/yaml.h"

#include "declare.h"

class Event
{
public:
  Event (Time t, std::string type): 
    m_occure_time(t),
    m_type(type)
  {}

  virtual ~Event (){}

  virtual void process() = 0;

  void save(YAML::Emitter &emitter) const;

  Time occuure_time() const {return m_occure_time;}
  std::string type() const {return m_type;}

private:
  Time m_occure_time;
  std::string m_type;
};
