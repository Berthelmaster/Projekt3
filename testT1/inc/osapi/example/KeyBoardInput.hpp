#ifndef KEYBOARD_INPUT_H_
#define KEYBOARD_INPUT_H_

#include <string>
#include <osapi/MsgQueue.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/example/LogSystem.hpp>

class KeyBoardInput : public osapi::ThreadFunctor
{
public:
  KeyBoardInput(LogSystem* l)
    : l_(l)
  {
  }
  
private:
  void run();

  LogSystem*      l_;
};
  
#endif
