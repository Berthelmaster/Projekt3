#pragma once
#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include "Messages.hpp"
#include <iostream>
#include <string>
#include <osapi/Utility.hpp>

class T1_webApp :public osapi::ThreadFunctor
{
public:
  T1_webApp(int size, osapi::MsgQueue *T2msgQ);
  virtual void run();
  void handler(osapi::Message* msg, unsigned long id);
  void sendCoffeeOrder(char, char, char);
  osapi::MsgQueue* getmsgQ();


private:
  osapi::MsgQueue*  mq_;
  osapi::MsgQueue*  T2Mq_;
};
