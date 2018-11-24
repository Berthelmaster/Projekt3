#include <osapi/Conditional.hpp>
#include <osapi/winx86/details/Conditional.hpp>


namespace osapi
{
  Conditional::Conditional()
    : cond_(new details::Conditional)
  {
  }
    
  void Conditional::signal()
  {
    cond_->signal();
  }
    
  void Conditional::broadcast()
  {
    cond_->broadcast();
  }

    
  void Conditional::wait(Mutex& mut)
  {
    cond_->wait(*mut.mut_);
  }
    
  Conditional::Awoken Conditional::waitTimed(Mutex& mut, unsigned long timeout)
  {
    return static_cast<Awoken>(cond_->waitTimed(*mut.mut_, timeout));
  }
    
  Conditional::~Conditional()
  {
    // Needed for incomplete type - MUST be in the cpp file where the pimpl is known!!!
	delete cond_;
  }
  
}

