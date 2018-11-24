#ifndef OSAPI_UTILITY_HPP
#define OSAPI_UTILITY_HPP



namespace osapi
{
  class Notcopyable
  {
  protected:
    Notcopyable() { }
    ~Notcopyable() { }

  private:
    Notcopyable(const Notcopyable&);
    const Notcopyable& operator=(const Notcopyable&);
  };

  template<typename T>
  class RAII : private Notcopyable
  {
  public:
    RAII(T* t)
      : t_(t)
    {
    }

    T* operator->()
    {
      return t_;
    }

    T* operator->() const
    {
      return t_;
    }

    T& operator*()
    {
      return *t_;
    }

    T& operator*() const
    {
      return *t_;
    }

    ~RAII()
    {
      delete t_;
    }

  private:
    T* t_;
  };


  void sleep(unsigned long msecs);
}



#endif
