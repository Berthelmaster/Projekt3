#include <errno.h>
#include <osapi/ConditionalError.hpp>
#include "osapi/linux/Mutex.hpp"
#include <osapi/linux/Conditional.hpp>

namespace osapi
{
  Conditional::Conditional()
  {
    if(pthread_condattr_init(&condattr_) != 0) throw ConditionalError();
    if(pthread_condattr_setclock(&condattr_, CLOCK_MONOTONIC) != 0) throw ConditionalError();
    if(pthread_cond_init(&cond_, &condattr_) != 0) throw ConditionalError();
  }

  void Conditional::signal()
  {
    pthread_cond_signal(&cond_);
  }

  void Conditional::broadcast()
  {
    pthread_cond_broadcast(&cond_);
  }

  void Conditional::wait(Mutex& mut)
  {
    pthread_cond_wait(&cond_, &mut.mut_);
  }

  Conditional::Awoken Conditional::waitTimed(Mutex& mut, unsigned long timeout)
  {
    struct timespec ts;

    // Get monotonic clock - current time
    clock_gettime(CLOCK_MONOTONIC, &ts);

    // Calculate new absolute time by getting current monotonic time and offsetting it
    size_t secs = timeout/1000;
    size_t msecs = timeout - secs*1000;

    ts.tv_sec += secs;
    ts.tv_nsec += msecs*1000000;
    size_t overflow = ts.tv_nsec/1000000000;

    if(overflow)
    {
      ts.tv_sec += overflow;
      ts.tv_nsec -= overflow*1000000000;
    }

    int res = pthread_cond_timedwait(&cond_, &mut.mut_, &ts);

    switch(res)
    {
      case ETIMEDOUT:
        return TIMEDOUT;
        break;

      case 0:
        return SIGNALED;
        break;

      default:
        throw ConditionalError();
    }
  }

  Conditional::~Conditional()
  {}

}
