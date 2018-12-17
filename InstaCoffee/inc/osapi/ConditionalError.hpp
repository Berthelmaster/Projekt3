#ifndef OSAPI_CONDERROR_HPP_
#define OSAPI_CONDERROR_HPP_

#include <osapi/Exceptions.hpp>

namespace osapi
{
  
  class ConditionalError : public SystemError
  {
  public:
    ConditionalError()
      : SystemError("Some conditional error occurred!")
    {}
    
  };

}

#endif
