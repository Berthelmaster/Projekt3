#include "SetTime.hpp"

#if defined(__arm__)
bool definitely_not_a_rpi = false;
#else
bool definitely_not_a_rpi = true;
#endif

  //std::string LineNumber = "4";
  //eraseFileLine("TimeLog.txt", LineNumber);

  // Max number time the machine will keep track on at the same time


int main(){

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
