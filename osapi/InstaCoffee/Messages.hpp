#pragma once
#include <osapi/Message.hpp>


#pragma once
#include "Message.h"
#include <iostream>

class CoffeeOrder : public Message {
  public:
    CoffeeOrder(char type, char strength, int size)
    {
      setCoffeeType(type);
      setCoffeeStrength(strength);
      setCupSize(size);
    }
    void setCoffeeType(char num)
    {
      if (num == '1' || num == '2')
        coffeeType_ = num;
      else
        std::cout << "Coffee Type not valid" << std::endl;
    }
    char getCoffeeType()
    {
      return coffeeType_;
    }
    void setCoffeeStrength(char strength)
    {
      if (strength > 0 && strength <= 3)
        coffeeStrength_ = strength;
      else
        std::cout << "Coffee strength not valid" << std::endl;
    }
    char getCoffeeStrength()
    {
      return coffeeStrength_;
    }
    void setCupSize(char size)
    {
      if (size> 0 && strength <= 3)
        cupSize_=((int)size-48+1)*10;//cupSize in cl achieved
      else
        std::cout << "Cup size not valid" << std::endl;
    }
    int getCupSize()
    {
      return cupSize_;
    }
    ~CoffeeOrder()
    {}
private:
    char coffeeType_ = '0';
    char coffeeStrength_ = '0';
    int cupSize_ = 0;
};

struct status: public osapi::Message
 {
   enum status{
     IDLE, BREWING, ERROR
   }
   status coffeeStatus_;
 }

enum
{

};
