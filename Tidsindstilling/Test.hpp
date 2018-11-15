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


void TimeMutex()
{

  while(1)
   {

   std::ifstream Fileloc; // Load User File
   Fileloc.open("TimefromUser.txt");
   std::stringstream strStream;
   strStream << Fileloc.rdbuf();
   std::string strUser = strStream.str();
   Fileloc.close();

   time_t rawtime;
	 struct tm * timeinfo;
	 char buffer[80];

   time(&rawtime);
	 timeinfo = localtime(&rawtime);

	 strftime(buffer, sizeof(buffer),"%H%M\n", timeinfo);
   std::string str(buffer);

	 std::cout << str << std::endl;
   std::cout << strUser << std::endl;

	if (strcmp(str.c_str(), strUser.c_str()) == 0)
	{
		std::cout << "Time is identical, Begin" << std::endl;
	}
  else
  {
    std::cout << "Time is not identical, try again" << std::endl;
  }

   sleep(1);

 }


}


int main()
{
  TimeMutex();
}
