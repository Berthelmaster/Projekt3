#ifndef OSAPI_ILOG_OUTPUT_HPP
#define OSAPI_ILOG_OUTPUT_HPP

#include <osapi/Time.hpp>
#include <osapi/LogTypes.hpp>

namespace osapi
{
  
  class ILogOutput
  {
  public:
    virtual void log(Level              lvl, 
                     const char*        fileName, 
                     int                lineNo, 
                     const char*        functionName,
                     Time               timeStamp,
                     const std::string& logString) = 0;

    virtual ~ILogOutput() 
    {}
    

  private:
  };

}

#endif
