#ifndef IHA_MESSAGE_HPP_
#define IHA_MESSAGE_HPP_

#ifdef BOOST_SUPPORT
#include <boost/shared_ptr.hpp>
#endif

namespace osapi
{
  class Message
  {
  public:
    virtual ~Message() {}
  };

#ifdef BOOST_SUPPORT
  typedef boost::shared_ptr<Message> MessagePtr;
#endif
}


#endif
