#include <osapi/ThreadError.hpp>
#include <osapi/Thread.hpp>
#include <osapi/winx86/details/Thread.hpp>

namespace osapi
{
	namespace
	{
	details::Thread::ThreadPriority conversionToDetail(Thread::ThreadPriority p)
	{
		switch(p)
		{
		case Thread::PRIORITY_LOW:
			return details::Thread::PRIORITY_LOW;
			break;

		case Thread::PRIORITY_BELOW_NORMAL:
			return details::Thread::PRIORITY_BELOW_NORMAL;
			break;

		case Thread::PRIORITY_NORMAL:
			return details::Thread::PRIORITY_NORMAL;
			break;

        case Thread::PRIORITY_ABOVE_NORMAL:
			return details::Thread::PRIORITY_ABOVE_NORMAL;
		    break;

		case Thread::PRIORITY_HIGH:
			return details::Thread::PRIORITY_HIGH;
			break;
		}
		throw ThreadError();
	}

	Thread::ThreadPriority conversionFromDetail(details::Thread::ThreadPriority p)
	{
		switch(p)
		{
		case details::Thread::PRIORITY_LOW:
			return Thread::PRIORITY_LOW;
			break;

		case details::Thread::PRIORITY_BELOW_NORMAL:
			return Thread::PRIORITY_BELOW_NORMAL;
			break;

		case details::Thread::PRIORITY_NORMAL:
			return Thread::PRIORITY_NORMAL;
			break;

        case details::Thread::PRIORITY_ABOVE_NORMAL:
			return Thread::PRIORITY_ABOVE_NORMAL;
		    break;

		case details::Thread::PRIORITY_HIGH:
			return Thread::PRIORITY_HIGH;
			break;
		}
		throw ThreadError();
	}

	}
  Thread::Thread(ThreadFunctor* tf,
                 Thread::ThreadPriority priority, 
                 const std::string& name,
                 bool autoStart)
    : thread_(new details::Thread(tf, conversionToDetail(priority), name, autoStart))
  {
  }


  Thread::~Thread()
  {
    delete thread_;
  }

  void Thread::start()
  {
    thread_->start();
  }


  std::string Thread::getName() const
  {
    return thread_->getName();
  }


  void Thread::setPriority(ThreadPriority priority) 
  {
    thread_->setPriority(conversionToDetail(priority));
  }


  Thread::ThreadPriority Thread::getPriority() const
  {
    return conversionFromDetail(thread_->getPriority());
  }


  void Thread::join()
  {
    thread_->join();
  }

  void Thread::detach()
  {
    thread_->detach();
  }

}
