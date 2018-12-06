#include <iostream>
#include <osapi/Exceptions.hpp>
#include <osapi/winx86/details/Mutex.hpp>

namespace osapi
{
  namespace details
  {
    
    Mutex::Mutex()
    {
      InitializeCriticalSection(&cs_);
    }

    void Mutex::lock()
    {
      EnterCriticalSection(&cs_);    
    }

    void Mutex::unlock()
    {
      LeaveCriticalSection (&cs_);
    }

    CRITICAL_SECTION& Mutex::nativeHandle()
    {
      return cs_;
    }
  

    Mutex::~Mutex()
    {
      DeleteCriticalSection(&cs_); // Ignores return value, may not through an exception anyway
    }
  
  }
  
}
