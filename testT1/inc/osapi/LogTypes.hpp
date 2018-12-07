#ifndef OSAPI_LOG_TYPES_HPP
#define OSAPI_LOG_TYPES_HPP

#include <string>
#include <exception>

namespace osapi
{
  enum Level 
  {
    Emergency = 0,
    Alert = 1,
    Critical = 2,
    Error = 3,
    Warning = 4,
    Notice = 5,
    Informational = 6,
    Debug = 7
  };
  enum 
  {
    LOG_LEVELS = Debug +1
  };
      
  extern const std::string LevelStr[];
  Level convertStrToLvl(const std::string& lvl);


  class LogLevelError : public std::exception
  {
  public: 
    LogLevelError(const std::string& error)
      : error_(error)
    {
    }
         
    virtual const char* what() const throw()
    {
      return error_.c_str();
    }
         
    virtual ~LogLevelError() throw()
    {
    }
         

  private:
    std::string error_;
  };
}






#endif
