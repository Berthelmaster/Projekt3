#include <osapi/ConditionalError.hpp>
#include <osapi/winx86/details/Mutex.hpp>
#include <osapi/winx86/details/Conditional.hpp>

namespace osapi
{
  namespace details
  {  
    Conditional::Conditional()
    {
      InitializeConditionVariable(&cond_);
    }


    void Conditional::signal()
    {
      WakeConditionVariable(&cond_);
    }


    void Conditional::broadcast()
    {
      WakeAllConditionVariable(&cond_);
    }


    void Conditional::wait(Mutex& mut)
    {
      if(!SleepConditionVariableCS (&cond_, &mut.nativeHandle(), INFINITE)) throw ConditionalError();
    }


    Conditional::Awoken Conditional::waitTimed(Mutex& mut, unsigned long timeout)
    {
      if(SleepConditionVariableCS (&cond_, &mut.nativeHandle(), timeout))
        return SIGNALED;
      else
      {
        int res = GetLastError();
        if((res == WAIT_TIMEOUT) || (res == ERROR_TIMEOUT))
          return TIMEDOUT;
        else
          throw ConditionalError();
      }
    }


    Conditional::~Conditional()
    {
      // No note in msdn about delete a conditional variable
    }
  }
  
}
