#ifndef OSAPI_LOG_HPP
#define OSAPI_LOG_HPP


#include <string>
#include <sstream>
#include "osapi/LogTypes.hpp"
#include <osapi/details/LogSystem.hpp>

#define LOG(lvl, ...) do { \
    std::stringstream ss;  \
    ss << __VA_ARGS__;                                     \
    osapi::details::LogSystem::getInstance()->log(__FILE__, __LINE__, __FUNCTION__, lvl, ss);   \
} while(0)

#define LOG_DETAIL(lvl, fileName, lineNo, functionName, ...) do { \
      std::stringstream ss; \
      ss << __VA_ARGS__; \
      osapi::details::LogSystem::getInstance()->log(fileName, lineNo, functionName, lvl, ss);     \
   } \
} while(0)

#define OSAPI_LOG_EMG(...) LOG(osapi::Emergency, __VA_ARGS__)
#define OSAPI_LOG_ALT(...) LOG(osapi::Alert, __VA_ARGS__)
#define OSAPI_LOG_CRT(...) LOG(osapi::Critical, __VA_ARGS__)
#define OSAPI_LOG_ERR(...) LOG(osapi::Error, __VA_ARGS__)
#define OSAPI_LOG_WRN(...) LOG(osapi::Warning, __VA_ARGS__)
#define OSAPI_LOG_NOT(...) LOG(osapi::Notice, __VA_ARGS__)
#define OSAPI_LOG_INF(...) LOG(osapi::Informational, __VA_ARGS__)
#define OSAPI_LOG_DBG(...) LOG(osapi::Debug, __VA_ARGS__)

namespace osapi
{
  void logSetNewOutput(ILogOutput* ilOutput);
}


#endif
