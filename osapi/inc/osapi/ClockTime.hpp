#ifndef OSAPI_CLOCK_TIME_HPP
#define OSAPI_CLOCK_TIME_HPP

#include <string>
#include <osapi/Time.hpp>


namespace osapi
{
  Time getCurrentMonotonicTime();
  Time getCurrentTime();
  std::string timeToStr(const Time& t, const std::string& format);
}


#endif
