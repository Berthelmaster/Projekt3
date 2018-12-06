#ifndef OSAPI_SEMAPHORE_ERROR_HPP_
#define OSAPI_SEMAPHORE_ERROR_HPP_

#include <osapi/Exceptions.hpp>

namespace osapi
{  
  class SemaphoreError : public SystemError
  {
  public:
    SemaphoreError()
      : SystemError("Some semaphore error occurred!")
    {}
    
  };
}

#endif
