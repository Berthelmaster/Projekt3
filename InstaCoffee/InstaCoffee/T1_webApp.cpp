#include "T1_webApp.hpp"

T1_webApp::T1_webApp(int size, osapi::MsgQueue *T2msgQ)
{
  mq_ = new MsgQueue(size);
  T2Mq_=T2msgQ;
  state_[0]='!';
  state_[1]='1';
  state_[2]='\0';

  h_.onMessage([this](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
      handleMessage(message,ws,opCode);
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
  }

} //end run

void T1_webApp::handler(osapi::Message* msg, unsigned long id)
{
  switch(id)
  {
    case(ID_STATUS_IND):
    {
      status* ind = static_cast<status*>(msg);
      state_[1]=ind->coffeeStatus_;
    }
    break;
  }
}

void T1_webApp::handleMessage(char *Message,uWS::WebSocket<uWS::SERVER> *ws,uWS::OpCode opCode)
{
  switch (Message[0])
  {
    case '!':
      getStatus();
      std::cout << state_ << '\n';
      ws->send(state_, 2, opCode);
      break;

    case '%':
      sendCoffeeOrder(Message[4],Message[1],Message[7]);
      ws->send("Coffee Ordered", 14, opCode);
      break;

    case '&':
      if(saveTXT(Message))
        ws->send("Brew time set", 13, opCode);
        else ws->send("Failed to set brew time", 23, opCode);

      break;
  }
}

void T1_webApp::sendCoffeeOrder(char size, char type, char strength)
{
  CoffeeOrder* ind = new CoffeeOrder(size, type, strength);
  T2Mq_->send(ID_COFFEE_ORDER_IND, ind);
}

bool T1_webApp::saveTXT(char *Message)
{
  std::string brewtime(++Message,25);
  std::ofstream logfile ("TimeLog.txt",std::ios::app);
  if (logfile.is_open())
  {
    logfile <<brewtime<<'\n';
    logfile.close();
  }
  else
  {
    std::cout << "Unable to save brewTime";
    return false;
  }
  std::cout <<brewtime<<'\n';
  return true;
}
void T1_webApp::getStatus()
{
  unsigned long id;
  osapi::Message* msg=mq_->receive(id);
  if (msg!=nullptr)
    handler(msg, id);
  delete msg;
}
