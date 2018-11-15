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
  UART()
  {
    open_port();

    // Get current serial port configuration
    tcgetattr(fd, &options);

    // Set baudrate
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    // Enable the receiver and set local mode
    options.c_cflag |= (CLOCAL | CREAD);

    // Set data bits, stopbit and parity
    options.c_cflag &= ~PARENB; // Disable parity bit with tilde(~)
    options.c_cflag &= ~CSTOPB; // Disable 2 stop bit with tilde(~)
    options.c_cflag &= ~CSIZE;  // Mask the character size bits
    options.c_cflag |= CS8;     // Select 8 data bits

    // Set the new options for the port
    tcsetattr(fd, TCSANOW, &options);

    // Makes read return 0, if nothing is in buffer, so it doesn't block up program
    // fcntl(fd, F_SETFL, FNDELAY);
    fcntl(fd, F_SETFL, 0);
  }

  char* readChar()
  {
    //ioctl(fd, FIONREAD, &bytes);
    int rdlen = read(fd, buf, 10);
    buf[rdlen] = '\0';
//    std::cout << "rdlen: " << rdlen << std::endl;

    if (rdlen > 0)
      return buf;
    else
      return readerr;
  }

  void writeBinary(char *message, int len)
  {
    int n = write(fd, message, len);
  }

  void writeChar(char *message)
  {
    int n = write(fd, message, sizeof(message));
    if (n < 0)
      fputs("write() of 1 byte failed!\n", stderr);
  }

  ~UART()
  {
    close(fd);
  }
private:
  void open_port()
  {
    fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1) //Could not open the port.
      perror("open_port: Unable to open /dev/ttyS0 - ");
    else
      fcntl(fd, F_SETFL, 0);
  }

  int bytes;
  int fd; //File desciptor
  char buf[10];
  struct termios options;
  char readerr[5] = "fejl";
};
