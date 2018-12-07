#ifndef OSAPI_MUTEXERROR_HPP_
#define OSAPI_MUTEXERROR_HPP_

#include <osapi/Exceptions.hpp>

namespace osapi
{
  
  class MutexError : public SystemError
  {
  public:
    MutexError()
      : SystemError("Some mutex error occurred!")
    {}
    
  };
}


#endif
