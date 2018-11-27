#include <osapi/Thread.hpp>

namespace osapi
{
  void* ThreadFunctor::threadMapper(void* thread)
  {
    ThreadFunctor* tf=static_cast<ThreadFunctor*>(thread);
    tf->run();
    tf->threadDone_.signal();
    return NULL;
  }
}
