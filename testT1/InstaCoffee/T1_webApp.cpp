#include "T1_webApp.hpp"

T1_webApp::T1_webApp(int size, osapi::MsgQueue *T2msgQ)
{
  mq_ = new MsgQueue(size);
  T2Mq_=T2msgQ;

  h_.onMessage([this](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
      std::cout << "Data: " << std::string_view(message, length) << std::endl; //udskriver beskeden

    switch (message[0])
    {
      case '!':
        ws->send("!1", 3, opCode);
        break;

      case '%':
        ws->send("Coffee Ordered", 14, opCode);
        sendCoffeeOrder(message[4],message[1],message[7]);
        std::cout<<message[1]<<message[4]<<message[7]<<'\n';
        break;

      case '&':
        ws->send("BrewTime set", 12, opCode);
        std::string brewtime(++message,25); //DEFINE!!!
        std::ofstream logfile ("TimeLog.txt",std::ios::app);
        if (logfile.is_open())
        {
          logfile <<brewtime<<'\n';
          logfile.close();
        }
        else std::cout << "Unable to save brewTime";
        std::cout <<brewtime<<'\n';
        break;
    }
});
}

MsgQueue* T1_webApp::getmsgQ()
{
  return mq_;
}

void T1_webApp::run()
{
  if (h_.listen(3000)) {
      h_.run();
    //  unsigned long id;
    //  osapi::Message* msg=mq_->receive(id);
    //  handler(msg, id);
    //  delete msg;
  }

} //end run

void T1_webApp::handler(osapi::Message* msg, unsigned long id)
{
  switch(id)
  {
    case(ID_STATUS_IND):
    {
      status* ind = static_cast<status*>(msg);
      state_=ind->coffeeStatus_;
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
