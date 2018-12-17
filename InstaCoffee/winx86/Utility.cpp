#include <windows.h>
#include <osapi/Utility.hpp>

namespace osapi
{
  
void sleep(unsigned long msecs)
{
  ::Sleep(msecs);
}

}

