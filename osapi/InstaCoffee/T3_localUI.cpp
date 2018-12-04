#include "T3_localUI.hpp"

T3_LocalUI::T3_LocalUI(osapi::MsgQueue *T2msgQ)
{
  std::cout<<"tråd 3 kører på klassen T3_localUI"<<std::endl;
  T2Mq_=T2msgQ;
}

void T3_LocalUI::run()
{
  //Alt funktionalitet skal ske herfra
}

void T3_LocalUI::sendCoffeeOrder(int size, int type, int strength)
{
  CoffeeOrder* ind = new CoffeeOrder(size, type, strength);
  ind->setCupSize(size);
  ind->setCoffeeType(type);
  ind->setCoffeeStrength(strength);
  T2Mq_->send(ID_COFFEE_ORDER_IND, ind);
}
