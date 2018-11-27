#include "T4T4_timeSetting.hpp"

T4_timeSetting::T4_timeSetting(osapi::MsgQueue *T2msgQ)
{
    T2Mq_=T2msgQ;
}

void T4_timeSetting::run()
{
  //Alt funktionalitet skal ske herfra
}

void T4_timeSetting::sendCoffeeOrder(int size, int type, int strength)
{
  CoffeeOrder* ind = new CoffeeOrder;
  ind.setCupSize(size);
  ind.setCoffeeType(type);
  ind.setCoffeeStrength(strength);
  T2Mq_->send(ID_COFFEE_ORDER_IND, ind)
}
