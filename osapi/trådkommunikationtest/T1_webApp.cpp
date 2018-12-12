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

  //Like whatever code u need
  while(true)
  {
    //osapi::sleep(1000);
    //getStatus();

  }
}

void T1_webApp::handler(osapi::Message* msg, unsigned long id)
{
  switch(id)
  {
    case(ID_STATUS_IND):
    {
      status* ind = static_cast<status*>(msg);
      //opdater status
      sendCoffeeOrder('1', '2', '3');
    }
    break;
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
  handler(msg, id);
  delete msg;
}
