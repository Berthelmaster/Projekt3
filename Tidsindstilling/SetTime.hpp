#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstring>
#include <vector>

std::string getTimeString()
{

  //Define variables
  int const size = 1024;
  std::fstream TimeFile;
  std::string line;
  std::string MyLine[size];
  std::string* myPointer = MyLine;


  TimeFile.open("TimefromUser.txt");

  if(TimeFile.is_open())
  {
    while(std::getline(TimeFile, line))
    {
        int i;
        MyLine[i] = line;
        std::cout << MyLine[i] << std::endl;
        sleep(1);
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

  std::cout << &MyLine[0] << std::endl;
  std::cout << &MyLine[1] << std::endl;
  std::cout << &MyLine[2] << std::endl;
  std::cout << &MyLine[3] << std::endl;
  std::cout << &MyLine[4] << std::endl;
  std::cout << MyLine[0] << std::endl;
  std::cout << MyLine[1] << std::endl;
  std::cout << MyLine[2] << std::endl;
  std::cout << MyLine[3] << std::endl;
  std::cout << MyLine[4] << std::endl;
  std::cout << myPointer << "Yoooo" << std::endl;

  return *myPointer;
}

std::string getCurrentTime()
{
  time_t rawtime;

  struct tm * timeinfo;

  char buffer[80];

  time(&rawtime);

  timeinfo = localtime(&rawtime);

  strftime(buffer, sizeof(buffer),"%H:%M-%Y-%m-%d", timeinfo);

  std::string str(buffer);

// Return value
  return str.c_str();
}

bool compareTime(std::string textFile, std::string RPITime)
{
  std::cout << textFile.c_str() << std::endl;
  std::cout << RPITime.c_str() << std::endl;
  if (strcmp(textFile.c_str(), RPITime.c_str()) == 0)
	{
    return true;
	}
  else
  {
    return false;
  }
}
