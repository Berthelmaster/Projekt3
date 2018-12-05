#include "T1_webApp.hpp"

T1_webApp::T1_webApp(int size, osapi::MsgQueue *T2msgQ)
{
  mq_ = new MsgQueue(size);
  T2Mq_=T2msgQ;
}

MsgQueue* T1_webApp::getmsgQ()
{
  return mq_;
}

void T1_webApp::run()
{
  sendCoffeeOrder('1', '2', '2');
  //Like whatever code u need
  while(true)
  {
    getStatus();
    osapi::sleep(1000);
  }
}

void T1_webApp::handler(osapi::Message* msg, unsigned long id)
{
  std::cout << "handlerT1" << '\n';
  std::cout << id << '\n';
  switch(id)
  {
    case(ID_STATUS_IND):
    {
      std::cout << "id læses korrekt" << '\n';
      status* ind = static_cast<status*>(msg);
      std::cout << ind->coffeeStatus_ <<"status skrives kan ikke korrekt ud"<< '\n';
      //opdater status
    }
    break;
    default:
    std::cout << "wrong ID" << '\n';
  }
}

void T1_webApp::sendCoffeeOrder(char size, char type, char strength)
{
  CoffeeOrder* ind = new CoffeeOrder(size, type, strength);
  T2Mq_->send(ID_COFFEE_ORDER_IND, ind);
}

void T1_webApp::getStatus()
{
  unsigned long id;
  osapi::Message* msg=mq_->receive(id);
  std::cout << "Id at whileloop"<<id << '\n';
  handler(msg, id);
  delete msg;
}
