/*  This file is made from the code of the webside, with modifications:
    https://www.cmrr.umn.edu/~strupp/serial
    Which is a Serial Programming Guide for POSIX Operating Systems.
*/
#pragma once
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <iostream>

class UART
{
public:
  UART();
  char readChar();
  void writeByte(char message);
  void writeChar(char message);
  char receiveStatus();
  void sendCoffeOrder(char filter, int waterAmount, char CoffeeNumber, int coffeeAmount);
  ~UART();
private:
  void open_port();
  int bytes;
  int fd; //File desciptor
  char buf[10];
  struct termios options;
};
