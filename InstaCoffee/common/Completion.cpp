#include <osapi/Completion.hpp>
#include <osapi/ScopedLock.hpp>

namespace osapi
{
  Completion::Completion()
    : done_(false)
  {
  }


  void Completion::wait()
  {
    ScopedLock sl(mut_);
    
    while(!done_)
      cond_.wait(mut_);
  }

  
  void Completion::signal()
  {
    ScopedLock sl(mut_);
    done_ = true;

    cond_.broadcast();
  }


  Completion::~Completion()
  {
  }
}
