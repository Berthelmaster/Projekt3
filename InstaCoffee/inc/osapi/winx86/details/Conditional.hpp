#ifndef OSAPI_WINX86_COND_DETAILS_HPP
#define OSAPI_WINX86_COND_DETAILS_HPP

#include <windows.h>
#include <osapi/Utility.hpp>
#include <osapi/ConditionalHelper.hpp>
#include <osapi/Mutex.hpp>

namespace osapi
{
  namespace details
  {
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
      CONDITION_VARIABLE   cond_;
    };
  }
}



#endif
