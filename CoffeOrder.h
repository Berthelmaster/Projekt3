#pragma once
#include "Message.h"
#include <iostream>

class CoffeeOrder : public Message {
public:
    CoffeeOrder()
    {}
    void setCoffeeNumber(char num)
    {
      if (num == '1' || num == '2')
        coffeeNumber = num;
      else
        std::cout << "Coffee Number not valid" << std::endl;
    }
    char getCoffeeNumber()
    {
      return coffeeNumber;
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
    char coffeeNumber = '0';
    char coffeeStrength = '0';
    int cupSize = 0;
};
