#ifndef OSAPI_WINX86_COND_HPP
#define OSAPI_WINX86_COND_HPP

#include <osapi/Utility.hpp>
#include <osapi/Mutex.hpp>

namespace osapi
{
  namespace details
  {
    class Conditional; // Forward declaration
  }   
  
  class Conditional : private Notcopyable
  {
  public:
    enum Awoken {
      SIGNALED=0,
      TIMEDOUT=1
    };    

    Conditional();
    void signal();
    void broadcast();
    void wait(Mutex& mut);
    Awoken waitTimed(Mutex& mut, unsigned long timeout);
    ~Conditional();
  private:
    details::Conditional*  cond_;
  };
}



#endif
