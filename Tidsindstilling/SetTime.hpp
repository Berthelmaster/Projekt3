#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstring>
#include <regex>

// 20 Kopper kaffe

int const size = 20;

std::string* getTimeString()
{
  //Define variables
  int i = 0;
  std::ifstream TimeFile;
  std::string line;
  static std::string MyLine[size];


  TimeFile.open("TimefromUser.txt");

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
  return str;
}

bool compareTime(std::string textFile, std::string RPITime)
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

char getFirstChar(std::string File1)
{
  std::string s = File1;
  std::regex theRegex(R"((\d+), \d+, \d+)");
  std::smatch result;
  std::regex_search(s, result, theRegex);
  std::string getresult = result.str(1);
  char rresult1 = getresult[0];

    return rresult1;
}

char getSecondChar(std::string File2)
{
  std::string s = File2;
  std::regex theRegex(R"(\d+, (\d+), \d+)");
  std::smatch result;
  std::regex_search(s, result, theRegex);
  std::string getresult = result.str(1);
  char rresult2 = getresult[0];

    return rresult2;
}

char getThirdChar(std::string File3)
{
  std::string s = File3;
  std::regex theRegex(R"(\d+, \d+, (\d+),)");
  std::smatch result;
  std::regex_search(s, result, theRegex);
  std::string getresult = result.str(1);
  char rresult3 = getresult[0];

    return rresult3;
}

/*
void deleteTimefromTxt(std::string File1)
{
  std::cout << UserTime.c_str() << std::endl;
}
*/
/*
void eraseFileLine(std::string path, std::string eraseLine) {
std::string line;
std::ifstream fin;

fin.open(path);
std::ofstream temp; // contents of path must be copied to a temp file then renamed back to the path file
temp.open("temp.txt");

while (getline(fin, line)) {
  line.replace(line.find(deleteline),deleteline.length(),"");
    temp << line << endl;
}

temp.close();
fin.close();

const char * p = path.c_str(); // required conversion for remove and rename functions
remove(p);
rename("temp.txt", p);}
*/