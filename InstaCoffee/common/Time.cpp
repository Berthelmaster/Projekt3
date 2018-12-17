#include <osapi/Time.hpp>
#include <iostream>

namespace osapi
{
  Time::Time()    
    :sec_(0), msec_(0)
  {}

  Time::Time(signed long sec, signed long long msec)    
    :sec_(sec + static_cast<signed long>(msec/1000)), msec_(msec%1000)
  {}


  Time::Time(signed long long msec)
    :sec_(static_cast<signed long>(msec/1000)), msec_(msec%1000)
  {}


  Time::Time(const Time& other)
    : sec_(other.sec_), msec_(other.msec_)
  {  
    //std::cout << __PRETTY_FUNCTION__ << std::endl;
  }
  


  Time& Time::operator+=(const Time& other)
  {
    msec_ += other.msec_;
    sec_  += other.sec_ + static_cast<signed long>(msec_/1000);
    msec_ %= 1000;
    return *this;
  }

  Time& Time::operator-=(const Time& other)
  {
    if(other.msec_ > msec_)
    {
      --sec_;
      msec_ += 1000;
    }
    
    msec_ -= other.msec_;
    sec_  -= other.sec_;
    return *this;
  }


  Time& Time::operator+=(signed long long msec)
  {
    msec_ += msec;
    sec_  += static_cast<signed long>(msec_/1000);
    msec_ %= 1000;
    return *this;    
  }  


  signed long long Time::secs() const
  {
    return sec_;
  }


  signed long long Time::msecs() const
  {
    return msec_;
  }


  signed long long Time::totalMSecs() const
  {
    signed long long result = sec_*1000;
    result += msec_;
    return result;
  }
  


  bool Time::operator<(const Time& other) const
  {
    if(sec_ < other.sec_)
      return true;
    
    if((msec_ < other.msec_) && (sec_ == other.sec_))
      return true;

    return false;
  }
  


  bool operator>(const Time& t1, const Time& t2)
  {
    return t2 < t1;
  }
  
  bool operator<=(const Time& t1, const Time& t2)
  {
    return !(t2<t1);
  }
  
  bool operator>=(const Time& t1, const Time& t2)
  {
    return !(t1<t2);    
  }
  



  Time operator+(Time t1, const Time& t2)
  {
    t1 += t2;
    return t1;
  }
  
  Time operator+(signed long long t1, Time t2)
  {
    t2 += t1;
    return t2;
  }
  
  Time operator+(Time t1, signed long long t2)
  {
    t1 += t2;
    return t1;
  }
  

  Time operator-(Time t1, const Time& t2)
  {
    t1 -= t2;
    return t1;
  }
  
  Time operator-(signed long long t1, Time t2)
  {
    t2 -= t1;
    return t1;
  }
  
  Time operator-(Time t1, signed long long t2)
  {
    t1 -= t2;
    return t1;
  }
  


}
