#include <iostream>
#include <osapi/Message.hpp>
#include <osapi/Time.hpp>
#include <osapi/ClockTime.hpp>
#include <osapi/Timer.hpp>
#include <osapi/ScopedLock.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Thread.hpp>
#include <osapi/Log.hpp>

namespace osapi
{
  
  // No error checking added - to keep it simpel, but this is not done in that respect    
  class TimerId;
  class ITimer : public ThreadFunctor
  {
  public:
    virtual void arm(ITimerId* iti, const Time& t) = 0;
    virtual void disArm(ITimerId* ti) = 0;
    
    Mutex& getLock();
    
    virtual ~ITimer() {}
  private:

  };

  namespace detail
  {
    ::osapi::ITimer* getInstance();

    typedef std::multimap< ::osapi::Time, TimerId*>     Container;
    typedef std::pair<Container::iterator, bool>        OptionalIterator;
    
  }
  



  class TimerId : public ITimerId
  {
  public:
    TimerId(MsgQueue* mq, unsigned long id);
    ~TimerId();
    
    void arm(unsigned long timeout, Message* m);
    void reArm(Message* m);
    void disArm();

    bool isCanceled() const; 
    void setCanceled();
    void setNotCanceled();
    void sendTimerMsg();
    detail::OptionalIterator& getContainerPos();

  private:
    Mutex                     mut_;
    Time                      armedTime_;
    unsigned long             timeOut_;
    MsgQueue*                 mq_;
    unsigned long             id_;
    Message*                  m_;
    bool                      canceled_;
    detail::OptionalIterator  containerPos_;
  };



  TimerId::TimerId(MsgQueue* mq, unsigned long id)
    :mq_(mq), id_(id), m_(NULL)
  {}  
  

  void TimerId::arm(unsigned long timeout, Message* m)
  {
    {
      ScopedLock sl(mut_);
      timeOut_    = timeout;
      armedTime_  = getCurrentMonotonicTime() + timeOut_;

      m_ = m;
      setNotCanceled();
    }
    
    detail::getInstance()->arm(this, armedTime_);
  }


  void TimerId::reArm(Message* m)
  {
    {
      
      ScopedLock sl(mut_);
      m_ = m;
      setNotCanceled();
      armedTime_ += timeOut_;
    }
    
    detail::getInstance()->arm(this, armedTime_);
  }


  void TimerId::disArm()
  {
    {
      
      ScopedLock sl(mut_);
      delete m_;  m_ = NULL;
      setCanceled();
    }
    
    detail::getInstance()->disArm(this);
  }


  bool TimerId::isCanceled() const
  {
    return canceled_;
  }

  
  void TimerId::setCanceled()
  {
    canceled_ = true;
  }


  void TimerId::setNotCanceled()
  {
    canceled_ = false;
  }


  void TimerId::sendTimerMsg() 
  {
    ScopedLock sl(mut_);
    mq_->send(id_, m_);
    m_ = NULL;
  }
  

  detail::OptionalIterator& TimerId::getContainerPos()
  {
    return containerPos_;
  }  


  TimerId::~TimerId()
  {
    try
    {
      disArm();    
    }
    catch(...)
    {
      // Do nothing...
    }    
  }  



  class Timer : public ITimer
  {
  public:
    Timer();
    
    void arm(ITimerId* iti, const Time& t);
    void disArm(ITimerId* ti);    

    ~Timer();

  private:      
    void run();
    void internalDisArm(TimerId* ti);


    bool                running_;
    Mutex               mut_;
    Conditional         cond_;

    detail::Container   container_;
  };


  Timer::Timer()
    : running_(true)
  {
    // Initialize posix stuff
  }


  Timer::~Timer()
  {
    // Send signal that we must terminate
    running_=false;
    cond_.signal();
  }  


  void Timer::run()
  {
    ScopedLock sl(mut_);
    for(;;)
    {
      // Wait until there is a timer...
      while(container_.empty() && running_)
        cond_.wait(mut_);

      if(!running_)
        break;

      // Get timeout for first timeout 
      Time deadline = container_.begin()->first;
      deadline -= getCurrentMonotonicTime();

      // Wait for timeout or plain old signal
      if ((deadline < 0) || (cond_.waitTimed(mut_, static_cast<unsigned long>(deadline.totalMSecs())) == Conditional::TIMEDOUT))
      {
        // Verify that what we waited is still legit and sending a timeout message is valid
        int i = 0;
        while(!container_.empty() && (container_.begin()->first <= getCurrentMonotonicTime()))
        {
          container_.begin()->second->sendTimerMsg();
          internalDisArm(container_.begin()->second);
          ++i;
        }  

      }
    }
  }


  void Timer::arm(ITimerId* iti, const Time& t)
  {
    TimerId* ti = static_cast<TimerId*>(iti);    
    {
      ScopedLock sl(mut_);

      ti->getContainerPos() = detail::OptionalIterator(std::make_pair(container_.insert(std::make_pair(t, ti)), true));
    }
    
    cond_.signal();
  }


  void Timer::internalDisArm(TimerId* ti)
  {
    if(ti->getContainerPos().second)
    {
      container_.erase(ti->getContainerPos().first);
      ti->getContainerPos() = detail::OptionalIterator(detail::Container::iterator(), false);
    }
  }


  void Timer::disArm(ITimerId* iti)
  {
    ScopedLock sl(mut_);
    internalDisArm(static_cast<TimerId*>(iti));
    
    cond_.signal(); // Ensure that timer thread is informed that certain changes have been performed.
  }

  
  ITimerId* createNewTimer(MsgQueue* mq, unsigned long id)
  {
    return new TimerId(mq, id);
  }
  

  namespace detail
  {
    ::osapi::ITimer* getInstance()
    {
      static ::osapi::Timer timer;
      static ::osapi::Thread t(&timer, Thread::PRIORITY_HIGH, "Timer Thread", true);
      return &timer;
    }
  }
}
