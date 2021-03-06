#include "T4_timeSetting.hpp"

// 20 Kopper kaffe

int const size = 20;

std::string* T4_timeSetting::getTimeString()
{
  //Define variables
  int i = 0;
  std::ifstream TimeFile;
  std::string line;
  static std::string MyLine[size];


  TimeFile.open("TimeLog.txt");

  if(TimeFile.is_open())
  {
    while(std::getline(TimeFile, line))
    {
        MyLine[i] = line;
        i++;
      //std::cout << MyLine[2] << std::endl;
      //std::cout << line.c_str() << std::endl;
    }
    TimeFile.close();
  }
  else
  {
    std::cout << "Timefile is not open" << std::endl;
  }

  return MyLine;
}

std::string T4_timeSetting::getCurrentTime()
{
  time_t rawtime;

  struct tm * timeinfo;

  char buffer[80];

  time(&rawtime);

  timeinfo = localtime(&rawtime);

  strftime(buffer, sizeof(buffer),"%H:%M-%Y-%m-%d", timeinfo);

  std::string str(buffer);

// Return value
  return str;
}

bool T4_timeSetting::compareTime(std::string textFile, std::string RPITime)
{

  std::string s = textFile;

   std::regex theRegex("^\\s*\\d+,\\s+\\d+,\\s+\\d+,\\s+(.*)");

   std::smatch result;

   std::regex_search(s, result, theRegex);

   std::string var = result.str(1);


  if (var == RPITime)
	{
    return true;
	}
  else
  {
    return false;
  }

}

char T4_timeSetting::getFirstChar(std::string File1)
{
  std::string s = File1;
  std::regex theRegex(R"((\d+), \d+, \d+)");
  std::smatch result;
  std::regex_search(s, result, theRegex);
  std::string getresult = result.str(1);
  char rresult1 = getresult[0];

    return rresult1;
}

char T4_timeSetting::getSecondChar(std::string File2)
{
  std::string s = File2;
  std::regex theRegex(R"(\d+, (\d+), \d+)");
  std::smatch result;
  std::regex_search(s, result, theRegex);
  std::string getresult = result.str(1);
  char rresult2 = getresult[0];

    return rresult2;
}

char T4_timeSetting::getThirdChar(std::string File3)
{
  std::string s = File3;
  std::regex theRegex(R"(\d+, \d+, (\d+),)");
  std::smatch result;
  std::regex_search(s, result, theRegex);
  std::string getresult = result.str(1);
  char rresult3 = getresult[0];

    return rresult3;
}

void T4_timeSetting::deleteTimefromTxt(const char *file_name, int n)
{
    // open file in read mode or in mode
    std::ifstream is(file_name);

    // open file in write mode or out mode
    std::ofstream ofs;
    ofs.open("temp.txt", std::ofstream::out);

    // loop getting single characters
    char c;
    int line_no = 1;
    while (is.get(c))
    {
        // if a newline character
        if (c == '\n')
        line_no++;

        // file content not to be deleted
        if (line_no != n)
            ofs << c;
    }

    // closing output file
    ofs.close();

    // closing input file
    is.close();

    // remove the original file
    remove(file_name);

    // rename the file
    rename("temp.txt", file_name);
}

T4_timeSetting::T4_timeSetting(osapi::MsgQueue *T2msgQ)
{
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
      sendCoffeeOrder(thirdChar, secondChar, firstChar);
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


void T4_timeSetting::sendCoffeeOrder(char size, char type, char strength)
{
  CoffeeOrder* ind = new CoffeeOrder(size, type, strength);
  ind->setCupSize(size);
  ind->setCoffeeType(type);
  ind->setCoffeeStrength(strength);
  T2Mq_->send(ID_COFFEE_ORDER_IND, ind);
}
