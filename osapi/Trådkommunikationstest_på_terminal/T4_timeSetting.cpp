#include "T4_timeSetting.hpp"

T4_timeSetting::T4_timeSetting(osapi::MsgQueue *T2msgQ)
{
  std::cout<<"tråd 4 kører på klassen T4_timeSetting"<<std::endl;
    T2Mq_=T2msgQ;
}

void T4_timeSetting::run()
{
  //Alt funktionalitet skal ske herfra
}

void T4_timeSetting::sendCoffeeOrder(int size, char type, char strength)
{
  CoffeeOrder* ind = new CoffeeOrder(size, type, strength);
  ind->setCupSize(size);
  ind->setCoffeeType(type);
  ind->setCoffeeStrength(strength);
  T2Mq_->send(ID_COFFEE_ORDER_IND, ind);
}
