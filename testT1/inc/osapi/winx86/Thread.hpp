#ifndef OSAPI_WINX86_THREAD_HPP
#define OSAPI_WINX86_THREAD_HPP

#include<string>
#include <osapi/Utility.hpp>
#include <osapi/ThreadFunctor.hpp>

namespace osapi
{
  namespace details
  {
    class Thread;
  }
  
  class Thread : Notcopyable
  {
  public:
	// Thread priorities
	enum ThreadPriority{
      PRIORITY_LOW,
      PRIORITY_BELOW_NORMAL,
      PRIORITY_NORMAL,
      PRIORITY_ABOVE_NORMAL,
      PRIORITY_HIGH
	};

	Thread(ThreadFunctor* tf, ThreadPriority pri = Thread::PRIORITY_NORMAL, const std::string& name = "", bool autoStart=false);
	~Thread();

	void start();
	void setPriority(ThreadPriority pri); 
	ThreadPriority getPriority() const;
    std::string getName() const;

    void join();
    void detach();

  private:
	details::Thread*   thread_;

  };
}

#endif
