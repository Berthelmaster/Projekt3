#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <streambuf>
#include <wchar.h>
#include <iostream>
#include <string.h>
#include <ctime>
#include <string>
#include <sstream>

std::string getTimeString()
{
  // Load User File
  std::ifstream Fileloc;
  // Open file "Filename"
  Fileloc.open("TimefromUser.txt");
  // Define stringstream
  std::stringstream strStream;
  // Read from file using rdbuf()
  strStream << Fileloc.rdbuf();
  // set string equals to strUser
  std::string strUser = strStream.str();
  // Close file
  Fileloc.close();

// Return value
  return strUser.c_str();
}

std::string getCurrentTime()
{
  time_t rawtime;

  struct tm * timeinfo;

  char buffer[80];

  time(&rawtime);

  timeinfo = localtime(&rawtime);

  strftime(buffer, sizeof(buffer),"%H%M\n", timeinfo);

  std::string str(buffer);

// Return value
  return str.c_str();
}
