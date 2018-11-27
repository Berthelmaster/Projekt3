#pragma once
#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include "Messages.hpp"
#include <iostream>
#include <string>
#include <osapi/Utility.hpp>

class T4_timeSetting :public osapi::ThreadFunctor
{
public:
  T4_timeSetting(osapi::MsgQueue *T2msgQ);
  virtual void run();
  void sendCoffeeOrder(int, int, int);

private:
  osapi::MsgQueue*  T2Mq_;
};
