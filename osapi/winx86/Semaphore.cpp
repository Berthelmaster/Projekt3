#include <osapi/Semaphore.hpp>
#include <osapi/winx86/details/Semaphore.hpp>

namespace osapi
{  
  Semaphore::Semaphore(unsigned int initCount)
    : 	sem_(new details::Semaphore(initCount))
  {
  }


  void Semaphore::wait()
  {
    sem_->wait();
  }


  void Semaphore::signal()
  {
    sem_->signal();
  }


  Semaphore::~Semaphore()
  {
    // Needed for incomplete type - MUST be in the cpp file where the pimpl is known!!!
	delete sem_;
  }

}
