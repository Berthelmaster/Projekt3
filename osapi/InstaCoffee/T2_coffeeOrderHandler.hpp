#pragma once
#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include "Messages.hpp"
#include <iostream>
#include <string>
#include <osapi/Utility.hpp>
#include "UARTHandler.h"

class T2_coffeOrderHandler :public osapi::ThreadFunctor
{
public:
  T2_coffeOrderHandler(int size);
  virtual void run();
  void handler(osapi::Message* msg, unsigned long id);
  void sendStatus();
  void setmsgQ(osapi::MsgQueue *msgQ);

private:
  osapi::MsgQueue*  mq_;
  osapi::MsgQueue*  T1Mq_;
  UARTHandler       UART_;
  ConvertToGrams    grams_;
  char              filter_=0;
};
