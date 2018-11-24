#include <iostream>
#include <osapi/example/KeyBoardInput.hpp>

void KeyBoardInput::run()
{
  for(;;)
  {
    std::string s;
    
    std::cin >> s;
    LogInd* logInd = new LogInd;
    logInd->text = s;
    l_->getMsgQueue()->send(LogSystem::ID_LOG_IND, logInd);
  }
  
}
