#include "ConvertToGram.h"



ConvertToGram::ConvertToGram()
{}

double ConvertToGram::getGrams(char size, char strength)
{
  size_=(int)size-48; //size håndteres som en int
  strength_=(((double)strength-48)/2)+2.5;
   //styrken bliver nu enten 3, 3.5 eller 4
  //en mild kop kaffe defineres til 3 gram pr. 100 gram
  //en mellem kop kaffe defineres til 3.5 gram pr. 100 gram
  //en stærk kop kaffe defineres til 4 gram pr. 100 gram
  grams_=strength_*(size_+1); //der ganges med size+1, der svarer til antal 100ml.
  return (int)grams_;
}
