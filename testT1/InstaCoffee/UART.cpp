
#include "UART.h"


UART::UART()
{
  open_port();

  // Get current serial port configuration
  tcgetattr(fd, &options);

  // Set baudrate
  cfsetispeed(&options, B57600);
  cfsetospeed(&options, B57600);

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

void UART::open_port()
{
  fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);

  if (fd == -1) //Could not open the port.
    perror("open_port: Unable to open /dev/ttyS0 - ");
  else
    fcntl(fd, F_SETFL, 0);
}

char UART::readChar()
{
  //ioctl(fd, FIONREAD, &bytes);
  int rdlen = read(fd, buf, 10);
  buf[rdlen] = '\0';

  if (rdlen > 0)
    return buf[0];
  else
    return '?';
}

void UART::writeByte(char message)
{
  int n = write(fd, &message, 1);
  if (n < 0)
    fputs("write() of 1 byte failed!\n", stderr);
}

void UART::writeChar(char message)
{
  int n = write(fd, &message, 1);
  if (n < 0)
    fputs("write() of 1 byte failed!\n", stderr);
}

char UART::receiveStatus()
{
  mut_.lock();
  char status;

  //initial startup message
  writeByte(1);
  writeByte(1);
  writeByte(1);

  writeByte(0x25);
  writeByte(0x0);

  //end com
  writeByte(0);
  writeByte(0);
  writeByte(0);

  status = readChar();

  mut_.unlock();
  return status;
}

void UART::sendCoffeOrder(char filter, char waterAmount, char CoffeeNumber, char coffeeAmount)
{
  mut_.lock();
  //initial startup message
  writeByte(1);
  writeByte(1);
  writeByte(1);

  // Chosen filter
  writeChar('$');
  writeByte(0x1);
  writeChar(filter-48);

  // Water amount
  writeChar('$');
  writeByte(0x4);
  writeByte(waterAmount);

  // Chosen coffee
  writeChar('$');
  if (CoffeeNumber == '1')
    writeByte(0x5);
  else
    writeByte(0x6);
  // coffee amount
  writeByte(14);

  writeByte(0);
  writeByte(0);
  writeByte(0);

  osapi::sleep(20);

  writeByte(1);
  writeByte(1);
  writeByte(1);
  //begin brewing
  writeChar('!');
  writeByte(0x0);

  //end com
  writeByte(0);
  writeByte(0);
  writeByte(0);

  mut_.unlock();
}

UART::~UART()
{
  close(fd);
}
