#include <osapi/ThreadError.hpp>
#include <osapi/winx86/details/Thread.hpp>

namespace osapi
{
  namespace details
  {

    Thread::Thread(ThreadFunctor* tf,
                   Thread::ThreadPriority priority, 
                   const std::string& name,
                   bool autoStart) 
      : tf_(tf), priority_(priority), name_(name), attached_(true)
    {
      if(autoStart)
        start();
    }


    Thread::~Thread()
    {
      try
      {
		  detach();
      }
      catch(...)
      {
        // Have to ignore, may not throw exception in destructor
      }
  
    }

    void Thread::start()
    {
      handle_ = CreateThread(NULL, 0, ThreadFunctor::threadMapper, tf_, 0, NULL);
      setPriority(priority_);
    }


    std::string Thread::getName() const
    {
      return name_;
    }


    void Thread::setPriority(ThreadPriority priority) 
    { 
      if(!SetThreadPriority(handle_, priority_)) throw ThreadError();
      priority_ = priority;
    }


    Thread::ThreadPriority Thread::getPriority() const
    {
      return priority_;
    }


    void Thread::join()
    {
	  if(attached_)
        tf_->threadDone_.wait();
    }

    void Thread::detach()
    {
	  if(attached_)
	  {
		  attached_ = false;
		  tf_ = NULL;
		  CloseHandle(handle_);
	  }
    }

  }
  
}
