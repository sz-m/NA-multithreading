#pragma once

#include <cstddef>
#include <array>
#include <mutex>
#include <thread>

template<typename T, std::size_t N>
class bounded_queue
{
public:
  void push_back(T t)
  {
    std::unique_lock<std::mutex> lock{ _mtx };

    while(_size == N)
    {
      lock.unlock();
      std::this_thread::yield();
      lock.lock();
    }

    _buffer[_back] = std::move(t);
    
    _back = (_back + 1) % N;
    ++_size;
  }

  T pop_front()
  {
    std::unique_lock<std::mutex> lock{ _mtx };

    while(_size == 0)
    {
      lock.unlock();
      std::this_thread::yield();
      lock.lock();
    }

    auto ret = _buffer[_front];

    _front = (_front + 1) % N;
    --_size;

    return ret;
  }


private:
  std::mutex _mtx;

  std::array<T, N> _buffer;
  std::size_t _front = 0;
  std::size_t _back = 0;
  std::size_t _size = 0;
};
