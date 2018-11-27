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

string getTimeString()
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
}

string getCurrentTime()
{

}

bool compareTime(string getTimeString, string getCurrentTime)
{

}

void deleteTimefromTxt()
{

}
