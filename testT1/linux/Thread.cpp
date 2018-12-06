#include <unistd.h>
#include <errno.h>
#include <iostream>
#include <osapi/Thread.hpp>


namespace osapi
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
    detach();
  }

  void Thread::start()
  {
    if(getuid() == 0) // Check to see if we are root
    {
      /* Steps to go through */
      pthread_attr_t  attr;
      if(pthread_attr_init(&attr) != 0) throw ThreadError();										// Init attr
      sched_param sched_p;
      if(pthread_attr_setschedpolicy(&attr, SCHED_RR) != 0) throw ThreadError();					// Set RR scheduling (RT, timesliced)
      if(pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED) != 0) throw ThreadError();	// Create thread with explicit (non-inherited) scheduling - setting priority will not work otherwise!
      sched_p.sched_priority = static_cast<int>(priority_);							// Set priority
      if(pthread_attr_setschedparam(&attr, &sched_p) != 0) throw ThreadError();					// Use the priority

      /* Thread creation */
      if(pthread_create(&threadId_, &attr, ThreadFunctor::threadMapper, tf_)!=0) throw ThreadError();

      pthread_attr_destroy(&attr);
    }
    else
    {
      /*Thread creation */
      if(pthread_create(&threadId_, NULL, ThreadFunctor::threadMapper, tf_)!=0) throw ThreadError();
    }
    // If ok no exception was thrown thus we have a valid thread and its attached!
    attached_ = true;
  }


  void Thread::setPriority(Thread::ThreadPriority priority)
  {
    if(!attached_) throw ThreadError();
    if(getuid() == 0) // Check to see if we are root
    {
      if(pthread_setschedprio(threadId_, static_cast<int>(priority)) != 0) throw ThreadError();
      priority_ = priority;
    }
    else
    {
      // Do nothing
    }
  }


  Thread::ThreadPriority Thread::getPriority() const
  {
    return priority_;
  }

  std::string Thread::getName()const
  {
    return name_;
  }


  void Thread::join()
  {
    if(!attached_) throw ThreadError();
    tf_->threadDone_.wait();
  }

  void Thread::detach()
  {
    if(!attached_) throw ThreadError();
    attached_ = false;
    tf_ = NULL;
    pthread_detach(threadId_);
  }

}
