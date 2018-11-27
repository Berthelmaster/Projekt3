#ifndef OSAPI_TIMER_HPP_
#define OSAPI_TIMER_HPP_

#include <map>
#include <osapi/Message.hpp>
#include <osapi/MsgQueue.hpp>

namespace osapi
{
  class ITimerId 
  {
  public:    
    virtual void arm(unsigned long timeout, Message* m = NULL) = 0;
    virtual void reArm(Message* m = NULL) = 0;
    virtual void disArm() = 0;

    virtual bool isCanceled() const = 0; 
    virtual ~ITimerId() { }
  protected:
  private:
  };
  
  ITimerId* createNewTimer(MsgQueue* mq, unsigned long id);
}


#endif
