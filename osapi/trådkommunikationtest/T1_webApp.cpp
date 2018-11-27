#include "T1_webApp.hpp"

T1_webApp::T1_webApp(int size, osapi::MsgQueue *T2msgQ)
{
  std::cout<<"tråd 1 kører på klassen T1_webApp"<<std::endl;
  mq_ = new osapi::MsgQueue(size);
  T2Mq_=T2msgQ;
}

osapi::MsgQueue* T1_webApp::getmsgQ()
{
  return mq_;
}

void T1_webApp::run()
{
  //Like whatever code u need
  while(1){
    sendCoffeeOrder('1', '1', '2');
    osapi::sleep(1000);



    unsigned long id;
    osapi::Message* msg=mq_->receive(id);
    handler(msg, id);
    delete msg;
  }
}

void T1_webApp::handler(osapi::Message* msg, unsigned long id)
{
  std::cout << "msg handled" << std::endl;

  switch(id)
  {
    case(ID_STATUS_IND):
    {
      status* ind = static_cast<status*>(msg);
      std::cout << ind->coffeeStatus_ <<std::endl;
      switch(ind->coffeeStatus_)
      {
        case(IDLE):
        {
          std::cout << "state idle" << std::endl;
        }
      }
      //opdater status
    }
    break;
  }
}

void T1_webApp::sendCoffeeOrder(char size, char type, char strength)
{
  CoffeeOrder* ind = new CoffeeOrder(size, type, strength);
  T2Mq_->send(ID_COFFEE_ORDER_IND, ind);
}
