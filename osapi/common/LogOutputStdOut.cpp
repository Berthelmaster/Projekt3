#include <iostream>
#include <osapi/ClockTime.hpp>
#include <osapi/LogOutputStdOut.hpp>


namespace osapi
{
  
  void LogOutputStdOut::log(Level              lvl, 
                            const char*        fileName, 
                            int                lineNo, 
                            const char*        functionName,
                            Time               timeStamp,
                            const std::string& logString)
  {
    std::cout << timeToStr(timeStamp, "%Y-%m-%d %H:%M:%S.") << timeStamp.msecs() 
              << " " << LevelStr[lvl] << " ("
              << fileName << ":" << lineNo << " - " << functionName << ") " << 
      logString << std::endl;
  }

}

