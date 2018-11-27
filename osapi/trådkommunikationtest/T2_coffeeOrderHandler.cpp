#include "T2_coffeeOrderHandler.hpp"

T2_coffeOrderHandler::T2_coffeOrderHandler(int size)
{
  std::cout<<"tråd 2 kører på klassen T2_coffeeOrderHandler"<<std::endl;
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
  //sendStatus();
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
  status* ind=new status;
  ind->coffeeStatus_=IDLE;
  T1Mq_->send(ID_STATUS_IND, ind);
  //do{
  /*
    char id = UART_.receiveStatus();

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
  //}
  //while(ind->status!=IDLE);
  */
}

void T2_coffeOrderHandler::handler(osapi::Message* msg, unsigned long id)
{
  switch(id)
  {
    case(ID_COFFEE_ORDER_IND):
    {
      CoffeeOrder* ind = static_cast<CoffeeOrder*>(msg);
      std::cout<<filter_<<endl;
      std::cout<< ind->getCupSize()<<endl;
      std::cout<< ind->getCoffeeType()<<std::endl;
      std::cout<< grams_.getGrams(ind->getCupSize(), ind->getCoffeeStrength())<<std::endl;
      //UART_.sendCoffeOrder(filter_, ind->getCupSize(), ind->getCoffeeType(), grams_.getGrams(ind->getCupSize(), ind->getCoffeeStrength()));
      if(++filter_>=8)
        filter_=0;
      sendStatus();
    }
    break;
  }
}
