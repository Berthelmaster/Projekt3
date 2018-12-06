#include <map>
#include <string>

#include "osapi/LogTypes.hpp"

namespace osapi
{
  const std::string LevelStr[] = 
  {
    "EMG",
    "ALT",
    "CRT",
    "ERR",
    "WRN",
    "NOT",
    "INF",
    "DBG"
  };

  namespace 
  {
    class StrToLvl
    {
    public:
      StrToLvl()
      {
        strLvl.insert(std::make_pair("emergency", Emergency));
        strLvl.insert(std::make_pair("EMG", Emergency));

        strLvl.insert(std::make_pair("alert", Alert));
        strLvl.insert(std::make_pair("ALT", Alert));

        strLvl.insert(std::make_pair("critical", Critical));
        strLvl.insert(std::make_pair("CRT", Critical));

        strLvl.insert(std::make_pair("error", Error));
        strLvl.insert(std::make_pair("ERR", Error));

        strLvl.insert(std::make_pair("warning", Warning));
        strLvl.insert(std::make_pair("WRN", Warning));
                  
        strLvl.insert(std::make_pair("notice", Notice));
        strLvl.insert(std::make_pair("NOT", Notice));

        strLvl.insert(std::make_pair("informational", Informational));
        strLvl.insert(std::make_pair("INF", Informational));

        strLvl.insert(std::make_pair("debug", Debug));
        strLvl.insert(std::make_pair("DBG", Debug));
      }

      Level operator()(const std::string& lvl)
      {
        std::map<std::string, Level>::const_iterator iter = strLvl.find(lvl);
                  
        if(iter == strLvl.end())
          throw LogLevelError(lvl + ", is not a valid log level name");
                  
        return iter->second;
      }
            
    private:
      std::map<std::string, Level>    strLvl;
    };
         
  }

  Level convertStrToLvl(const std::string& lvl)
  {
    static StrToLvl   stl;
         
    return stl(lvl);
  }
      

}
