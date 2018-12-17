#ifndef LOG_SYSTEM_H_
#define LOG_SYSTEM_H_

#include <string>
#include <fstream>
#include <osapi/MsgQueue.hpp>
#include <osapi/ThreadFunctor.hpp>

struct LogInd : public osapi::Message
{
  std::string text;
};


class LogSystem : public osapi::ThreadFunctor
{
public:
  enum {
    ID_LOG_IND
  };
  static const int MAX_QUEUE_SIZE = 10;
  LogSystem()
    : mq_(MAX_QUEUE_SIZE), lf_("log.txt")
  {
  }
  
  osapi::MsgQueue* getMsgQueue()
  {
    return &mq_;
  }
    
private:
  void writeToLog(LogInd* l);
  void handleMsg(unsigned long id, osapi::Message* msg);
  void run();

  osapi::MsgQueue mq_;
  std::ofstream   lf_;
};
  
#endif
