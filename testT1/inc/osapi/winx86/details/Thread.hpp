#ifndef OSAPI_WINX86_THREAD_DETAILS_HPP
#define OSAPI_WINX86_THREAD_DETAILS_HPP

#include<string>
#include<windows.h>
#include<osapi/ThreadFunctor.hpp>

namespace osapi
{
  namespace details
  {
	  class Thread
	  {
	  public:
		// Thread priorities
		enum ThreadPriority{
		  PRIORITY_LOW          = THREAD_PRIORITY_LOWEST,
		  PRIORITY_BELOW_NORMAL = THREAD_PRIORITY_BELOW_NORMAL,
		  PRIORITY_NORMAL       = THREAD_PRIORITY_NORMAL,
		  PRIORITY_ABOVE_NORMAL = THREAD_PRIORITY_ABOVE_NORMAL,
		  PRIORITY_HIGH         = THREAD_PRIORITY_HIGHEST,
		};

		Thread(ThreadFunctor* tf, ThreadPriority pri = Thread::PRIORITY_NORMAL, const std::string& name = "", bool autoStart = false);
		~Thread();

		void start();
		void setPriority(ThreadPriority pri); 
		ThreadPriority getPriority() const;
		std::string getName() const;

		void join();
		void detach();

	  private:
        ThreadFunctor*  tf_;
		ThreadPriority priority_;
		std::string    name_;
		HANDLE         handle_;
		bool           attached_;

	  };
  }
}

#endif
