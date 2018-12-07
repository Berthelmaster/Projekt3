#include "T2_coffeeOrderHandler.hpp"

T2_coffeOrderHandler::T2_coffeOrderHandler(int size, UART* u)
{
  mq_ = new osapi::MsgQueue(size);
  UART_ = u;
  //other init
}

void T2_coffeOrderHandler::setmsgQ(MsgQueue *msgQ)
{
  T1Mq_=msgQ;
}

osapi::MsgQueue* T2_coffeOrderHandler::getmsgQ()
{
  return mq_;
}

void T2_coffeOrderHandler::run()
{
  for(int i=0;i<10;i++){
    status* ind=new status;
    ind->coffeeStatus_=IDLE;
    ind->coffeeStatus_=status_.coffeeStatus_;
    T1Mq_->send(ID_STATUS_IND, ind);
  }

  status* ind=new status;
  ind->coffeeStatus_=BREWING;
  T1Mq_->send(ID_STATUS_IND, ind);
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
  std::cout << "send status" << '\n';
  status* ind=new status;
  ind->coffeeStatus_=ERROR;
  T1Mq_->send(ID_STATUS_IND, ind);
  /*
  do{
    char id = UART_->receiveStatus();
    //  char id='2';
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
    if(ind->coffeeStatus_!=status_.coffeeStatus_){
      T1Mq_->send(ID_STATUS_IND, ind);
      status_.coffeeStatus_=ind->coffeeStatus_;
    }
  } while(ind->coffeeStatus_!=IDLE);
*/
}

void T2_coffeOrderHandler::handler(osapi::Message* msg, unsigned long id)
{
  std::cout << "handlerT2" << '\n';
  switch(id)
  {
    case(ID_COFFEE_ORDER_IND):
    {
      std::cout << "id" << '\n';
      CoffeeOrder* ind = static_cast<CoffeeOrder*>(msg);
      //UART_.sendCoffeOrder(filter_, ind->getCupSize(), ind->getCoffeeType(), grams_.getGrams(ind->getCupSize(), ind->getCoffeeStrength()));
      if(++filter_>=8)
        filter_=0;
      status_.coffeeStatus_=BREWING;
      sendStatus();
    }
    break;
  }
}