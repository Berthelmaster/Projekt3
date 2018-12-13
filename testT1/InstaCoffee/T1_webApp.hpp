#pragma once
#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include "Messages.hpp"
#include <iostream>
#include <string>
#include <osapi/Utility.hpp>
#include "MsgQueue.h"
#include <string_view> //TILFØJET
#include <uWS/uWS.h> //TILFØJET
#include <fstream> //TILFØJET

class T1_webApp :public osapi::ThreadFunctor
{
public:
  T1_webApp(int size, osapi::MsgQueue *T2msgQ);
  virtual void run();
  void handler(osapi::Message* msg, unsigned long id);
  void handleMessage(char *Message,uWS::WebSocket<uWS::SERVER> *ws,uWS::OpCode opCode);
  void sendCoffeeOrder(char, char, char);
  bool saveTXT(char * Message);
  MsgQueue* getmsgQ();
  void getStatus(uWS::WebSocket<uWS::SERVER> *ws);


private:
  MsgQueue*  mq_;
  osapi::MsgQueue*  T2Mq_;
  uWS::Hub h_;
  char  state_;
};
