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

  //while(queue_.size() == 0)
    //reader_.wait(mut_);
  Item i = queue_.front();
  queue_.pop_front();

  mut_.unlock();

  id=i.id_;
  return i.msg_;
}

unsigned long MsgQueue::size() const
{
  return queue_.size();
}
