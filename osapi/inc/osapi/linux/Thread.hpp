#ifndef OSAPI_LINUX_THREAD_HPP
#define OSAPI_LINUX_THREAD_HPP

#include <pthread.h>
#include <string>

#include <osapi/ThreadError.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Completion.hpp>


namespace osapi
{
  class Thread
  {
  public:
    enum ThreadPriority
    {
      PRIORITY_LOW = 15,
      PRIORITY_BELOW_NORMAL = 30,
      PRIORITY_NORMAL = 45,
      PRIORITY_ABOVE_NORMAL = 60,
      PRIORITY_HIGH = 75
    };

    Thread(ThreadFunctor* tf,
           ThreadPriority p = PRIORITY_NORMAL,
           const std::string& name="",
           bool autoStart = false);
    virtual ~Thread();
    void start();
    void setPriority(Thread::ThreadPriority p);
    ThreadPriority getPriority() const;
    std::string getName() const;

    void join();
    void detach();

  private:
    ThreadFunctor*  tf_;
    ThreadPriority  priority_;
    std::string     name_;
    pthread_t       threadId_;
    bool            attached_;
  };
  
}

#endif
