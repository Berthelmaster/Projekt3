#ifndef OSAPI_COMPLETION_HPP
#define OSAPI_COMPLETION_HPP

#include <osapi/Conditional.hpp>
#include <osapi/Mutex.hpp>

namespace osapi {
  
  class Completion
  {
  public:
    Completion();
    void wait();
    void signal();
    ~Completion();
  private:
    bool          done_;
    Conditional   cond_;
    Mutex         mut_;
  };

}


#endif
