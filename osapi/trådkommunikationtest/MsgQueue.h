#pragma once
#include <deque>
#include <osapi/Mutex.hpp>
#include <osapi/Conditional.hpp>
#include <osapi/Message.hpp>
#include <string>
#include <iostream>


class MsgQueue
{
public:
  MsgQueue(unsigned long maxSize);
  void send(unsigned long id, osapi::Message* msg = nullptr);
  osapi::Message* receive(unsigned long &id);
  unsigned long size() const;

private:
  struct Item
  {
    Item(unsigned long id, osapi::Message* m)
      : id_(id), msg_(m) { }

    unsigned long   id_;
    osapi::Message*      msg_;
  };
  typedef std::deque<Item>  Queue;
  Queue                     queue_;
  unsigned long             MaxSize_;
  osapi::Mutex              mut_;
  osapi::Conditional        reader_, writer_;
};
