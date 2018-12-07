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
  uWS::Hub h;

    h.onMessage([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
        std::cout << "Data: " << std::string_view(message, length) << std::endl; //udskriver beskeden

      switch (message[0])
      {
        case '!':
          unsigned long id;
          osapi::Message* msg=mq_->receive(id);
          //handler(msg, id, ws);
          switch(id)
          {
            case(ID_STATUS_IND):
            {
              status* ind = static_cast<status*>(msg);
              char* status=ind->coffeeStatus_;

              ws->send(status, 2, opCode);
            }
            break;
          }
          delete msg;


          break;

        case '%':
          ws->send("Coffee Ordered", 14, opCode);
          sendCoffeeOrder(message[1],message[4],message[7]);
          std::cout<<message[1]<<message[4]<<message[7]<<'\n';

          break;

        case '&':
          ws->send("BrewTime set", 12, opCode);
          break;
      }
  });
  if (h.listen(3000)) {
      h.run();
  }
} //end run

void T1_webApp::handler(osapi::Message* msg, unsigned long id)
{
  switch(id)
  {
    case(ID_STATUS_IND):
    {
      status* ind = static_cast<status*>(msg);
    //  ws->send(ind->coffeeStatus_, 2, opCode);
    }
    break;
  }
}

void T1_webApp::sendCoffeeOrder(char size, char type, char strength)
{
  CoffeeOrder* ind = new CoffeeOrder(size, type, strength);
  T2Mq_->send(ID_COFFEE_ORDER_IND, ind);
}

void T1_webApp::getStatus(uWS::WebSocket<uWS::SERVER> *ws)
{
  unsigned long id;
  osapi::Message* msg=mq_->receive(id);
  //handler(msg, id, ws);
  delete msg;
}
