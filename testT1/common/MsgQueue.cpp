#include <osapi/MsgQueue.hpp>

namespace osapi
{
  
MsgQueue::MsgQueue(unsigned long maxSize)
  : maxSize_(maxSize)
{
}

void MsgQueue::send(unsigned long id, MessagePtr mp)
{
  
  mut_.lock();
  
  while(queue_.size() == maxSize_)
    writer_.wait(mut_);

  queue_.push_back(Item(id, mp));
  mut_.unlock();
  reader_.signal();
}

MessagePtr MsgQueue::receive(unsigned long& id)
{
  mut_.lock();
  
  while(queue_.size() == 0)
    reader_.wait(mut_);
  
  Item i = queue_.front();
  queue_.pop_front();

  writer_.signal();
  
  mut_.unlock();

  id = i.id_;
  return i.mp_;
}


MsgQueue::~MsgQueue()
{
}

}
