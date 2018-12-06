
#include <time.h>
#include <osapi/ClockTime.hpp>

namespace osapi
{
  Time getCurrentMonotonicTime()
  {
    struct timespec ts;

    // Get monotonic time
    clock_gettime(CLOCK_MONOTONIC, &ts);
    
    return Time(ts.tv_sec, ts.tv_nsec/1000000L);
  }

  Time getCurrentTime()
  {
    struct timespec ts;

    // Get monotonic time
    clock_gettime(CLOCK_REALTIME, &ts);
    
    return Time(ts.tv_sec, ts.tv_nsec/1000000L);
  }

  std::string timeToStr(const Time& t, const std::string& format)
  {
    const int MAX_RESULT=64;
    struct tm timeStruct;
    time_t tt = t.secs();
    gmtime_r(&tt, &timeStruct);

    std::string result;
    
    result.resize(MAX_RESULT+1);
    strftime(&result[0], MAX_RESULT, format.c_str(), &timeStruct);
    return result;
  }
  

  
}
