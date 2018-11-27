#ifndef OSAPI_SCOPED_LOCK_HPP
#define OSAPI_SCOPED_LOCK_HPP

#include <osapi/Mutex.hpp>


namespace osapi
{
  class ScopedLock
  {
  public:
    ScopedLock(Mutex& mut)
      : mut_(mut), taken_(true)
    {
      mut_.lock();
    }

    void unlock()
    {
      mut_.unlock();
      taken_ = false;
    }
    
    void lock()
    {
      mut_.lock();
      taken_ = true;      
    }
    
    ~ScopedLock()
    {
      if(taken_)
        mut_.unlock();
    }
    
    
  private:
    Mutex& mut_;
    bool taken_;
  };
    
}


#endif
