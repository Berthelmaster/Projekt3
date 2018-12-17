#include "MsgQueue.h"

MsgQueue::MsgQueue(unsigned long maxSize):MaxSize_(maxSize)
{}

void MsgQueue::send(unsigned long id, osapi::Message* msg)
{
  mut_.lock();

  while(queue_.size() != 0)
    queue_.pop_front();

  queue_.push_back(Item(id, msg));
  mut_.unlock();
}

osapi::Message* MsgQueue::receive(unsigned long &id)
{
  mut_.lock();
  
    if(size()!=0){
      Item i = queue_.front();
      queue_.pop_front();
      mut_.unlock();
      id=i.id_;
      return i.msg_;
    }
    mut_.unlock();
    return nullptr;
}

unsigned long MsgQueue::size() const
{
  return queue_.size();
}
