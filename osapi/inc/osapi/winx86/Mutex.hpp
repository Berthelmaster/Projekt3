#ifndef OSAPI_WINX86_MUTEX_HPP
#define OSAPI_WINX86_MUTEX_HPP

#include <osapi/Utility.hpp>

namespace osapi
{
  // Forward declaration, needed for friend designation
  class Conditional;
  
  namespace details
  {
    class Mutex; // Forward declaration
  }
  
  class Mutex : Notcopyable
  {
  public:
    Mutex();
    void lock();
    void unlock();
    ~Mutex();
  private:
    friend class Conditional;

    details::Mutex*   mut_;
  };  
}



#endif
