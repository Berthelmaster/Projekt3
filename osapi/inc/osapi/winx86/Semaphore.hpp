#ifndef OSAPI_WINX86_SEMAPHORE_HPP
#define OSAPI_WINX86_SEMAPHORE_HPP

#include <osapi/Utility.hpp>

namespace osapi
{
  namespace details
  {
    class Semaphore;
  }

  class Semaphore : Notcopyable
  {
  public:
    Semaphore(unsigned int initCount);
    void wait();
    void signal();
    ~Semaphore();
  private:
    details::Semaphore*   sem_;
  };
}

#endif
