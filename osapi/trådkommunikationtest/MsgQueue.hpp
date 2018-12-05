#ifndef IHA_MSG_QUEUE_HPP_
#define IHA_MSG_QUEUE_HPP_

#include <deque>
#include <algorithm>
#ifdef BOOST_SUPPORT
#include <boost/shared_ptr.hpp>
#endif
#include <osapi/Mutex.hpp>
#include <osapi/Conditional.hpp>
#include <osapi/Message.hpp>

  template<typename M>
  class BasicMsgQueue
  {
  public:
    BasicMsgQueue(unsigned long maxSize);

    void send(unsigned long id, M m = M());
    M receive(unsigned long& id);
    unsigned long size() const;

    ~BasicMsgQueue();
  private:
    struct Item
    {
      Item(unsigned long id, M m)
        : id_(id), m_(m) { }

      unsigned long   id_;
      M               m_;
    };



    typedef std::deque<Item> Queue;
    unsigned long     maxSize_;
    Queue             queue_;
    Mutex             mut_;
    Conditional       reader_, writer_;
  };

  namespace detail
  {
    struct MapItemDeleter
    {
      template<typename T>
      void operator()(T t)
      {
        delete t.m_;
      }

    };
  }


  /* Defines */
  typedef BasicMsgQueue<Message*>         MsgQueue;

#ifdef BOOST_SUPPORT
  typedef boost::shared_ptr<Message>      MessagePtr;
  typedef BasicMsgQueue<MessagePtr>       MsgPtrQueue;
  typedef boost::shared_ptr<MsgQueue>     MsgQueuePtr;
  typedef boost::shared_ptr<MsgPtrQueue>  MsgPtrQueuePtr;
#endif

  /* Implementation */

  template<typename M>
  BasicMsgQueue<M>::BasicMsgQueue(unsigned long maxSize)
    : maxSize_(maxSize)
  {
  }


  template<typename M>
  void BasicMsgQueue<M>::send(unsigned long id, M m)
  {
    mut_.lock();

    while(queue_.size() == 0){
      queue_.pop_front();
    }

    queue_.push_back(Item(id, m));
    mut_.unlock();
    reader_.signal();
  }


  template<typename M>
  M BasicMsgQueue<M>::receive(unsigned long& id)
  {
    mut_.lock();

    while(queue_.size() == 0)
      reader_.wait(mut_);

    Item i = queue_.front();
    queue_.pop_front();

    writer_.signal();

    mut_.unlock();

    id = i.id_;
    return i.m_;

  }


  template<typename M>
  unsigned long BasicMsgQueue<M>::size() const
  {
    return queue_.size();
  }

  template<typename M>
  BasicMsgQueue<M>::~BasicMsgQueue()
  {
    std::for_each(queue_.begin(), queue_.end(), detail::MapItemDeleter());
  }




#endif
