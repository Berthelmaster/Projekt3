#ifndef OSAPI_WINX86_MUTEX_DETAILS_HPP
#define OSAPI_WINX86_MUTEX_DETAILS_HPP
#include <windows.h>
#include <osapi/Utility.hpp>

namespace osapi
{
  namespace details
  {    
    class Mutex : Notcopyable
    {
    public:
      Mutex();
      void lock();
      void unlock();
      CRITICAL_SECTION& nativeHandle();
      ~Mutex();
    private:
      CRITICAL_SECTION cs_;
    };
  }
  
}



#endif
