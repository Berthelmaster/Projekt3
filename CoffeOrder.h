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
        coffeeType = num;
      else
        std::cout << "Coffee Type not valid" << std::endl;
    }
    char getCoffeeType()
    {
      return coffeeType;
    }
    void setCoffeeStrength(char strength)
    {
      if (strength < 0 || strength > 5)
        coffeeStrength = strength;
      else
        std::cout << "Coffee strength not valid" << std::endl;
    }
    char getCoffeeStrength()
    {
      return coffeeStrength;
    }
    void setCupSize(char size)
    {
      if (size == '1')
        cupSize = 200;
      else if (size == '2')
        cupSize = 300;
      else if (size == '3')
        cupSize = 400;
      else
        std::cout << "Cup size not valid" << std::endl;
    }
    int getCupSize()
    {
      return cupSize;
    }
    ~CoffeeOrder()
    {}
private:
    char coffeeType = '0';
    char coffeeStrength = '0';
    int cupSize = 0;
};
