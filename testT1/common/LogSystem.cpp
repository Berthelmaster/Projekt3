#include <osapi/ClockTime.hpp>
#include <osapi/LogOutputStdOut.hpp>
#include <osapi/Log.hpp>
#include <iostream>

namespace osapi
{
  namespace details
  {
    void LogSystem::setNewOutput(ILogOutput* ilOutput)
    {
      SetNewOutput* setNewOutput = new SetNewOutput;
      setNewOutput->ilOutput_ = ilOutput;
      mq_.send(ID_SET_NEW_OUTPUT, setNewOutput);
    }  


    
    void LogSystem::setLogLvl(Level lvl)
    {
      SetLogLvl* setLogLvl = new SetLogLvl;
      setLogLvl->lvl_ = lvl;
      mq_.send(ID_SET_LOG_LVL, setLogLvl);
    }  


    void LogSystem::log(const char* fileName, int lineNo, 
                        const char* functionName, 
                        Level lvl,
                        const std::stringstream& ss)
    {
      Log* log = new Log;
      log->timeStamp_     = getCurrentTime();
      log->fileName_      = fileName;
      log->lineNo_        = lineNo;
      log->functionName_  = functionName;
      log->lvl_           = lvl;
      log->logString_     = ss.str();
      mq_.send(ID_LOG, log);
    }
  

    LogSystem::LogSystem()
      : mq_(MAX_LOG_MSG), running_(true), lvl_(Debug), logOutput_(new LogOutputStdOut)
    {
    }


    LogSystem::~LogSystem()
    {
       mq_.send(ID_TERMINATE);
      // join();
      // delete logOutput_;
    }
    

    void LogSystem::handleSetNewOutput(SetNewOutput* setNewOutput)
    {
      delete logOutput_;
      logOutput_ = setNewOutput->ilOutput_;
    }


    void LogSystem::handleSetLogLvl(SetLogLvl* setLogLvl)
    {
      lvl_ = setLogLvl->lvl_;
    }
  

    void LogSystem::handleLog(Log* log)
    {
      logOutput_->log(log->lvl_, 
                      log->fileName_, 
                      log->lineNo_,
                      log->functionName_,
                      log->timeStamp_,
                      log->logString_);
    }
  

    void LogSystem::handleMsg(unsigned long id, Message* msg)
    {
      switch(id)
      {
        case ID_SET_NEW_OUTPUT:
          handleSetNewOutput(static_cast<SetNewOutput*>(msg));
          break;
          
        case ID_SET_LOG_LVL:
          handleSetLogLvl(static_cast<SetLogLvl*>(msg));
          break;
        
        case ID_LOG:
          handleLog(static_cast<Log*>(msg));
          break;

        case ID_TERMINATE:
          running_ = false;
          break;
          
        default:
          std::cout << "Very bad, not known id" << std::endl;
          break;
      }
    
    }


    void LogSystem::run()
    {
      while(running_)
      {
        unsigned long id;
        Message* msg = mq_.receive(id);
        handleMsg(id, msg);
        delete msg;
      }
    }
  
  




    ::osapi::details::LogSystem* LogSystem::getInstance()
    {
      static ::osapi::details::LogSystem ls;
	  static ::osapi::Thread t(&ls, ::osapi::Thread::PRIORITY_NORMAL, "LogSystem Thread", true);
      
      
      return &ls;
    }


  }
    
}
