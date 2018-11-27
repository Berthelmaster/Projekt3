#include <osapi/ThreadFunctor.hpp>
#include <osapi/Thread.hpp>

namespace osapi
{
  DWORD WINAPI ThreadFunctor::threadMapper(void* thread)
  {
    /* Something is missing here - Determine what! */
    tf->threadDone_.signal();
    return NULL;
  }

}
