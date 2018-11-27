#ifndef OSAPI_LINUX_THREADFUNCTOR_HPP
#define OSAPI_LINUX_THREADFUNCTOR_HPP

#include <osapi/Completion.hpp>

namespace osapi
{
  class Thread;
  class ThreadFunctor
  {
  public:

  protected:
    virtual void run() = 0;
    ~ThreadFunctor(){} // Protected destructor -> cant delete thread object via base pointer.
    
  private:
    friend class osapi::Thread;    
    
    Completion      threadDone_;
    static void* threadMapper(void* p);
  };
}


#endif
