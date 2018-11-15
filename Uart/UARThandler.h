#pragma once
#include "UART.h"
#include <unistd.h>
#include <stdint.h>

class UARThandler
{
  public:
    UARThandler()
    {}

    char receivestatus()
    {
      char status;
      uart.write('%');
      uart.write(0);
      sleep(1);
      status = uart.read();
      return status;
    }

    void sendCoffeorder(char filter, uint8_t cL, char CoffeeNumber, uint8_t coffeeamount)
    {
      uart.write('$');

      // Start filling water tank
      uart.write(5);
      uart.write(cL);

      // Chosen filter
      uart.write(1);
      uart.write(filter);

      // Chosen coffee
      if (CoffeeNumber == '1')
        uart.write(6);
      else
        uart.write(7);

      // Dispense coffee
      uart.write(coffeeamount);
      uart.write('!');
      uart.write(1);
      uart.write(0);
    }

    ~UARThandler
    {}
  private:
    UART uart;
};
