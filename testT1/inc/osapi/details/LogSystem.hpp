#ifndef OSAPI_LOG_SYSTEM_HPP
#define OSAPI_LOG_SYSTEM_HPP

#include <string>
#include <osapi/Time.hpp>
#include <osapi/Thread.hpp>
#include <osapi/Message.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/LogTypes.hpp>
#include <osapi/ILogOutput.hpp>

namespace osapi
{
  namespace details
  {
    struct SetNewOutput : public Message
    {
      ILogOutput* ilOutput_;
    };
    
      
    
    struct SetLogLvl : public Message
    {
      Level   lvl_;
    };

    struct Log : public Message
    {
      Level                     lvl_;
      const char*               fileName_;
      int                       lineNo_;
      const char*               functionName_; 
      Time                      timeStamp_;
      std::string               logString_;
    };

    


    class LogSystem : public ThreadFunctor
    {
    public:
      static LogSystem* getInstance();

      void setNewOutput(ILogOutput* ilOutput);
      void setLogLvl(Level lvl);
      void log(const char* fileName, int lineNo, const char* functionName, Level lvl,
               const std::stringstream& ss);
    private:
      LogSystem();
      ~LogSystem();
      
      void handleSetNewOutput(SetNewOutput* setNewOutput);
      void handleSetLogLvl(SetLogLvl* setLogLvl);
      void handleLog(Log* log);
      void handleMsg(unsigned long id, Message* msg);
      void run();

      enum { MAX_LOG_MSG=100 
      };
      
      enum { ID_SET_NEW_OUTPUT,
             ID_SET_LOG_LVL,
             ID_LOG,
             ID_TERMINATE
      };

      MsgQueue    mq_;
      bool        running_;
      Level       lvl_;
      ILogOutput* logOutput_;
    };
    

    ::osapi::details::LogSystem* getInstance();    

  }

}


#endif
