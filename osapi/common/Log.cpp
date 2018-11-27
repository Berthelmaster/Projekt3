#include <osapi/Log.hpp>
#include <osapi/details/LogSystem.hpp>
namespace osapi
{
  void logSetNewOutput(ILogOutput* ilOutput)
  {
    details::LogSystem::getInstance()->setNewOutput(ilOutput);
  }
  
}
