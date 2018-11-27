#include "ConvertToGram.h"


int main(){
  ConvertToGram C;
  double d;
  d=C.getGrams(10, '1');
  cout <<d<<endl;
  d=C.getGrams(20, '1');
  cout <<d<<endl;
  d=C.getGrams(30, '1');
  cout <<d<<endl;
  d=C.getGrams(10, '2');
  cout <<d<<endl;
  d=C.getGrams(20, '2');
  cout <<d<<endl;
  d=C.getGrams(30, '2');
  cout <<d<<endl;
  d=C.getGrams(10, '3');
  cout <<d<<endl;
  d=C.getGrams(20, '3');
  cout <<d<<endl;
  d=C.getGrams(30, '3');
  cout <<d<<endl;
}
