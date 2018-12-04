#pragma once
#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include "Messages.hpp"
#include <iostream>
#include <string>
#include <osapi/Utility.hpp>
#include "UART.h"

class T3_LocalUI :public osapi::ThreadFunctor
{
public:
  T3_LocalUI(osapi::MsgQueue *T2msgQ, UART* u);
  virtual void run();
  void sendCoffeeOrder(int, int, int);

private:
  osapi::MsgQueue*  T2Mq_;
  UART*             UART_;
};
