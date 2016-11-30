#pragma once

#include <cstddef>
#include <array>
#include <mutex>
#include <thread>
#include <condition_variable>

template<typename T, std::size_t N>
class bounded_queue
{
public:
  void push_back(T t)
  {
    std::unique_lock<std::mutex> lock{ _mtx };

    while(_size == N)
    {
      _full_queue.wait(lock);
    }

    _buffer[_back] = std::move(t);
    
    _back = (_back + 1) % N;
    ++_size;

    _empty_queue.notify_one();

  }

  T pop_front()
  {
    std::unique_lock<std::mutex> lock{ _mtx };

    while(_size == 0)
    {
      _empty_queue.wait(lock);
    }

    auto ret = _buffer[_front];

    _front = (_front + 1) % N;
    --_size;

    _full_queue.notify_one();

    return ret;
  }


private:
  std::mutex _mtx;
  std::condition_variable _full_queue;
  std::condition_variable _empty_queue;

  std::array<T, N> _buffer;
  std::size_t _front = 0;
  std::size_t _back = 0;
  std::size_t _size = 0;
};
