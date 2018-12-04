#include "UART.h"


UART::UART()
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
  char status;
  writeChar('%');
  writeByte(0x0);
  status = readChar();
  return status;
}

void UART::sendCoffeOrder(char filter, int waterAmount, char CoffeeNumber, int coffeeAmount)
{

  writeChar('$');

  // Start filling water tank
  writeByte(0x5);
  writeByte(waterAmount);

  // Chosen filter
  writeByte(0x1);
  writeChar(filter);

  // Chosen coffee
  if (CoffeeNumber == '1')
    writeByte(0x6);
  else
    writeByte(0x7);

  // Dispense coffee
  writeByte(coffeeAmount);
  writeChar('!');
  writeByte(0x1);
  writeByte(0x0);

}

UART::~UART()
{
  close(fd);
}
