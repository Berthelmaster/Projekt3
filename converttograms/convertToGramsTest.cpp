#include "ConvertToGram.h"


int main(){
  ConvertToGram C;
  double d;
  d=C.getGrams('1', '1');
  cout <<d<<endl;
  d=C.getGrams('2', '1');
  cout <<d<<endl;
  d=C.getGrams('3', '1');
  cout <<d<<endl;
  d=C.getGrams('1', '2');
  cout <<d<<endl;
  d=C.getGrams('2', '2');
  cout <<d<<endl;
  d=C.getGrams('3', '2');
  cout <<d<<endl;
  d=C.getGrams('1', '3');
  cout <<d<<endl;
  d=C.getGrams('2', '3');
  cout <<d<<endl;
  d=C.getGrams('3', '3');
  cout <<d<<endl;
}
