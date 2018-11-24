#include <osapi/Thread.hpp>
//#include <Console.hpp>
#include <osapi/example/LogSystem.hpp>
#include <osapi/example/KeyBoardInput.hpp>

int main()
{
  //Console c;
  LogSystem l;
  KeyBoardInput k(&l);
  
  //osapi::Thread ct(&c);
  osapi::Thread lt(&l);
  lt.start();
  osapi::Thread kt(&k);
  kt.start();

  //ct.join();
  lt.join();
  kt.join();
  
}
