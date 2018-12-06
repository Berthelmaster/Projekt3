#ifndef OSAPI_TIME_HPP
#define OSAPI_TIME_HPP

namespace osapi
{
  class Time
  {
  public:
    Time();
    Time(signed long sec, signed long long msec);
    Time(signed long long msec);

    Time(const Time& other);

    Time& operator+=(const Time& other);
    Time& operator-=(const Time& other);
    Time& operator+=(signed long long msec);
    
    signed long long secs() const;
    signed long long msecs() const;

    signed long long totalMSecs() const;


    bool operator<(const Time& other) const;

  private:
    signed long       sec_;
    signed long long  msec_;
  };
  
  bool operator>(const Time& t1, const Time& t2);
  bool operator<=(const Time& t1, const Time& t2);
  bool operator>=(const Time& t1, const Time& t2);

  Time operator+(Time t1, const Time& t2);
  Time operator+(signed long long t1, Time t2);
  Time operator+(Time t1, signed long long t2);

  Time operator-(Time t1, const Time& t2);
  Time operator-(signed long long t1, Time t2);
  Time operator-(Time t1, signed long long t2);

}

#endif
