#ifndef OSAPI_EXCEPTIONS_HPP
#define OSAPI_EXCEPTIONS_HPP

#include <stdexcept>

namespace osapi
{
  
class SystemError : public std::runtime_error
{
public:
  SystemError(const std::string& what_arg)
    : std::runtime_error(what_arg)
  {}
private:
};

}

#endif
