#include <windows.h>
#include <time.h>
#include <osapi/ClockTime.hpp>

namespace osapi
{
  Time getCurrentMonotonicTime()
  {    
    return Time(GetTickCount64());
  }

  Time getCurrentTime()
  {
	const long long int EPOCH_DIFF=0x019DB1DED53E8000LL; /* 116444736000000000 nsecs */
    const long long int RATE_DIFF=10000; /* 100 usecs */

    FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	// Convert it to the internal Time class
    ULARGE_INTEGER ularge;
    ularge.LowPart=ft.dwLowDateTime;
    ularge.HighPart=ft.dwHighDateTime;
	return Time((ularge.QuadPart - EPOCH_DIFF) / RATE_DIFF);
  }

  std::string timeToStr(const Time& t, const std::string& format)
  {
    const int MAX_RESULT=64;
    struct tm timeStruct;
    time_t tt = t.secs();
    gmtime_s(&timeStruct, &tt);

    std::string result;
    
    result.resize(MAX_RESULT+1);
    result.resize(strftime(&result[0], MAX_RESULT, format.c_str(), &timeStruct));
    return result;
  }

  
}
