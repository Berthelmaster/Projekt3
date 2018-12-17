#pragma once
#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include "Messages.hpp"
#include <iostream>
#include <string>
#include <osapi/Utility.hpp>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <regex>

class T4_timeSetting :public osapi::ThreadFunctor
{
public:
  T4_timeSetting(osapi::MsgQueue *T2msgQ);
  virtual void run();
  void sendCoffeeOrder(char, char, char);
  std::string* getTimeString();
  std::string getCurrentTime();
  bool compareTime(std::string textFile, std::string RPITime);
  char getFirstChar(std::string File1);
  char getSecondChar(std::string File2);
  char getThirdChar(std::string File3);
  void deleteTimefromTxt(const char *file_name, int n);

private:
  osapi::MsgQueue*  T2Mq_;
};