#ifndef OSAPI_THREADERROR_HPP
#define OSAPI_THREADERROR_HPP

#include <osapi/Exceptions.hpp>

namespace osapi
{
  class ThreadError : public SystemError
  {
  public:
    ThreadError()
      : SystemError("Some thread error occurred!")
    {}
    
  };
}


#endif
