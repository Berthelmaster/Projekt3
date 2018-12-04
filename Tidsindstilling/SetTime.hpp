#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstring>

std::string getTimeString()
{
  std::fstream TimeFile;
  std::string line;

  TimeFile.open("TimefromUser.txt");

  if(TimeFile.is_open())
  {
    while(std::getline(TimeFile, line))
    {
      //std::cout << line.c_str() << std::endl;
      sleep(1);
    }
    TimeFile.close();
  }
  else
  {
    std::cout << "Timefile is not open" << std::endl;
  }

  return line.c_str();
}

std::string getCurrentTime()
{
  time_t rawtime;

  struct tm * timeinfo;

  char buffer[80];

  time(&rawtime);

  timeinfo = localtime(&rawtime);

  strftime(buffer, sizeof(buffer),"%H%M", timeinfo);

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
		std::cout << "Time is identical, Begin" << std::endl;
    return true;
	}
  else
  {
    std::cout << "Time is not identical, try again" << std::endl;
    return false;
  }
}
