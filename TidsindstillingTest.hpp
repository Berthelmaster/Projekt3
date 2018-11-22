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



// TimeMutex
void TimeMutex()
{

	std::ifstream t("TimefromUser.txt");

	do {
		// Manipulate txt file here
		std::ifstream Fileloc; // Load User File
		Fileloc.open("TimefromUser.txt");
		std::stringstream strStream;
		strStream << Fileloc.rdbuf();
		std::string strUser = strStream.str();
		Fileloc.close();


		// Get time from Computer here
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(buffer, sizeof(buffer), "%H%M", timeinfo);
		std::string str(buffer);

		// Print both strings for testing
		std::cout << str << std::endl;
		std::cout << strUser << std::endl;


		// Compare the two strings to see if they are identical
		if (strcmp(str.c_str(), strUser.c_str()) == 0)
		{
			std::cout << "Send Class Here Now!" << std::endl;
			exit(1);
		}
		else
		{
			std::cout << "Time is not identical, try again" << std::endl;
		}
		// Sleep and try againm
		sleep(1);
	} while (t.peek() == std::ifstream::traits_type::eof() == 0);

}



// Test in main function
int main()
{
	TimeMutex();
}
