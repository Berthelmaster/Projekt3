#include "T2_coffeeOrderHandler.hpp"

T2_coffeOrderHandler::T2_coffeOrderHandler(int size)
{
  mq_ = new osapi::MsgQueue(size);
  //Uartconfig???
  //other init?
}

void T2_coffeOrderHandler::setmsgQ(osapi::MsgQueue *msgQ)
{
  T1Mq_=msgQ;
}

osapi::MsgQueue* T2_coffeOrderHandler::getmsgQ()
{
  return mq_;
}

void T2_coffeOrderHandler::run()
{
  sendStatus();
  while(true)
  {
    unsigned long id;
    osapi::Message* msg=mq_->receive(id);
    handler(msg, id);
    delete msg;
  }
}

void T2_coffeOrderHandler::sendStatus()
{
  do{
    char id = UART_.receiveStatus();
    status* ind=new status;
    switch(id)
    {
      case('1'):
      {
        ind->coffeeStatus_=IDLE;
      }
      break;
      case('2'):
      {
        ind->coffeeStatus_=BREWING;
      }
      break;
      case('3'):
      {
        ind->coffeeStatus_=ERROR;
      }
      break;
    }
    T1Mq_->send(ID_STATUS_IND, ind);
  }
  while(ind->status!=IDLE);
}

void T2_coffeOrderHandler::handler(osapi::Message* msg, unsigned long id)
{
  switch(id)
  {
    case(ID_COFFEE_ORDER_IND):
    {
      CoffeeOrder* ind = static_cast<CoffeeOrder*>(msg);
      UART_.sendCoffeOrder(filter, ind->cupSize_, ind->coffeeType_, grams_.getGrams(ind->cupSize_, ind->coffeeStrength_));
      if(++filter>=8)
        filter=0;
      sendStatus();
    }
    break;
  }
}
