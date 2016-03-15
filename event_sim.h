#include <queue>
#include <functional>

class Event
{
public:
  Event (unsigned t): m_occure_time(t){}
  virtual ~Event ();

  virtual void process() = 0;
  unsigned occuure_time() const {return m_occure_time;}
  std::function<bool (Event*, Event*)>compare; 

private:
  unsigned m_occure_time;

};

class Simulator
{
public:
  Simulator (): m_time(0){}
  virtual ~Simulator ();

  void run();

private:
  unsigned m_time;
  
  std::priority_queue<
    Event*, 
    std::vector<Event*>, 
    decltype(Event::compare)> m_event_queue;

};
