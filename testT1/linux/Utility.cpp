#include <osapi/Utility.hpp>
#include <unistd.h>

namespace osapi
{
  void sleep(unsigned long msecs)
  {
    usleep(msecs*1000);
  }
}
