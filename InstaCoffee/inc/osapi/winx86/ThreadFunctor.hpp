#ifndef OSAPI_WINX86_THREADFUNCTOR_HPP
#define OSAPI_WINX86_THREADFUNCTOR_HPP

#include <osapi/Completion.hpp>

namespace osapi
{
	namespace details
	{
		class Thread;
	}
  class ThreadFunctor
  {
  protected:
    virtual void run() = 0;
    
  private:
    friend class details::Thread;

    Completion      threadDone_;
    static DWORD WINAPI threadMapper(void* p) ;
  };
}


#endif
