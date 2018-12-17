#ifndef OSAPI_LINUX_SEMAPHORE_HPP
#define OSAPI_LINUX_SEMAPHORE_HPP

#include <semaphore.h>
#include <osapi/Utility.hpp>

namespace osapi
{
  class Semaphore : Notcopyable
  {
  public:
    Semaphore(unsigned int initCount);
    void wait();
    void signal();
    ~Semaphore();
  private:
	sem_t semId_;
  };
}



#endif
