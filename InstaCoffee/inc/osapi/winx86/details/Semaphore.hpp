#ifndef OSAPI_WINX86_SEMAPHORE_DETAILS_HPP
#define OSAPI_WINX86_SEMAPHORE_DETAILS_HPP

#include <windows.h>
#include <osapi/Utility.hpp>

namespace osapi
{
	namespace details
	{
	  class Semaphore : Notcopyable
	  {
	  public:
		Semaphore(unsigned int initCount);
		void wait();
		void signal();
		~Semaphore();
	  private:
		HANDLE id_;
	  };
	}
}



#endif
