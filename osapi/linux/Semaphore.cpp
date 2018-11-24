#include <osapi/Semaphore.hpp>

namespace osapi
{  
  Semaphore::Semaphore(unsigned int initCount)
  {
    if(sem_init(&semId_, 1, initCount) != 0) throw SemaphoreError();
  }


  void Semaphore::wait()
  {
    if(sem_wait(&semId_) != 0) throw SemaphoreError();
  }


  void Semaphore::signal()
  {
    if(sem_post(&semId_) != 0) throw SemaphoreError();
  }


  Semaphore::~Semaphore()
  {
    sem_destroy(&semId_);
  }

}
