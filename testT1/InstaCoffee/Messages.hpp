#pragma once
#include <osapi/Message.hpp>
#include <osapi/MsgQueue.hpp>

#include <iostream>

class CoffeeOrder : public osapi::Message {
  public:
    CoffeeOrder(char size, char type, char strength)
    {
      setCoffeeType(type);
      setCoffeeStrength(strength);
      setCupSize(size);
    }

    void setCoffeeType(char num)
    {
      if (num == '1' || num == '2')
        coffeeType_ = num;
    }

    char getCoffeeType()
    {
      return coffeeType_;
    }

    void setCoffeeStrength(char strength)
    {
      if (strength > '0' && strength <= '3')
        coffeeStrength_ = strength;
    }

    char getCoffeeStrength()
    {
      return coffeeStrength_;
    }

    void setCupSize(char size)
    {
      if (size> '0' && size <= '3')
        cupSize_=((int)size-48+1)*10;//cupSize in cl achieved
    }

    int getCupSize()
    {
      return cupSize_;
    }

    ~CoffeeOrder()
    {}

private:
    char coffeeType_ = '1';
    char coffeeStrength_ = '2';
    int cupSize_ = 20;
};

enum
{
  ID_COFFEE_ORDER_IND, ID_STATUS_IND, IDLE='1', BREWING='2', ERROR='3'
};

struct status: public osapi::Message
 {
   char coffeeStatus_=IDLE;
 };
