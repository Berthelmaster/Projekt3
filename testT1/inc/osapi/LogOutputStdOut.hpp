#ifndef OSAPI_LOG_OUTPUT_STDOUT_HPP
#define OSAPI_LOG_OUTPUT_STDOUT_HPP

#include <osapi/ILogOutput.hpp>

namespace osapi
{
  
  class LogOutputStdOut : public ILogOutput
  {
  public:
    virtual void log(Level              lvl, 
                     const char*        fileName, 
                     int                lineNo, 
                     const char*        functionName,
                     Time               timeStamp,
                     const std::string& logString);
  };

}

  


#endif
