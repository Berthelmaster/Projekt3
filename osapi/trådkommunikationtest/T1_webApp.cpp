#include "T1_webApp.hpp"

T1_webApp::T1_webApp(int size, osapi::MsgQueue *T2msgQ)
{
  mq_ = new osapi::MsgQueue(size);
  T2Mq_=T2msgQ;
}

osapi::MsgQueue* T1_webApp::getmsgQ()
{
  return mq_;
}

void T1_webApp::run()
{
  sendCoffeeOrder('1', '2', '2');
  //Like whatever code u need
  std::cout << "run" << '\n';
  while(true){
    unsigned long id;
    osapi::Message* msg=mq_->receive(id);
    handler(msg, id);
    delete msg;
  }
}

void T1_webApp::handler(osapi::Message* msg, unsigned long id)
{
  std::cout << "handlerT1" << '\n';
  switch(id)
  {
    case(ID_STATUS_IND):
    {
      //status* ind = static_cast<status*>(msg);
      //opdater status

    }
    break;
  }
}

void T1_webApp::sendCoffeeOrder(char size, char type, char strength)
{
  std::cout << "send" << '\n';
  CoffeeOrder* ind = new CoffeeOrder(size, type, strength);
  T2Mq_->send(ID_COFFEE_ORDER_IND, ind);
}
