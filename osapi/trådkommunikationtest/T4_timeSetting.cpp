#include "T4_timeSetting.hpp"

T4_timeSetting::T4_timeSetting(osapi::MsgQueue *T2msgQ)
{
  std::cout<<"tråd 4 kører på klassen T4_timeSetting"<<std::endl;
    T2Mq_=T2msgQ;
}

void T4_timeSetting::run()
{
  while(1)
  {

    for(int j = 0; j < size; j++ ){
    std::string* fromfile = getTimeString();
    std::string fromRPI = getCurrentTime();
    std::string ToFunction = fromfile[j];
    compareTime(ToFunction, fromRPI);
    {
      bool condition = compareTime(ToFunction, fromRPI);
      if(condition == true){
      char firstChar = getFirstChar(ToFunction);
      char secondChar = getSecondChar(ToFunction);
      char thirdChar = getThirdChar(ToFunction);

      std::cout << "Sending Data: " << ToFunction << std::endl;
      std::cout << "First Coffee Paramter is: " << firstChar << std::endl;
      std::cout << "Second Coffee Paramter is: " << secondChar << std::endl;
      std::cout << "Third Coffee Paramter is: " << thirdChar << std::endl;
      const char* nameOfFile = "TimeLog.txt";
      int lineNuumber = j + 1;
      deleteTimefromTxt(nameOfFile, lineNuumber);
      std::cout << "Deleted the following line: " << ToFunction << std::endl;
      sleep(60);
      }
      if(condition == false && j == 19)
      {
        std::cout << "No Data to send - You are Coff-free" << std::endl;
        sleep(13);

      }


    }
  }
}
}

void T4_timeSetting::sendCoffeeOrder(int size, char type, char strength)
{
  CoffeeOrder* ind = new CoffeeOrder(size, type, strength);
  ind->setCupSize(size);
  ind->setCoffeeType(type);
  ind->setCoffeeStrength(strength);
  T2Mq_->send(ID_COFFEE_ORDER_IND, ind);
}
