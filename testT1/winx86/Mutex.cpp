#include <osapi/Mutex.hpp>
#include <osapi/winx86/details/Mutex.hpp>


namespace osapi
{
  Mutex::Mutex()
    : mut_(new details::Mutex)
  {
  }

  void Mutex::lock()
  {
    mut_->lock();
  }
  
  void Mutex::unlock()
  {
    mut_->unlock();
  }

  Mutex::~Mutex()
  {
    // Needed for incomplete type - MUST be in the cpp file where the pimpl is known!!!
	delete mut_;
  }
  
}
