#pragma once

#include <cstddef>
#include <condition_variable>
#include <mutex>

class semaphore
{
public:
  semaphore(std::size_t count = 0) : _count{count}
  {
  }
  
  void wait()
  {
    std::unique_lock<std::mutex> lock{_mtx};
    _cv.wait(lock, [&](){ return _count != 0; });
    --_count;
  }

  bool try_wait()
  {
    std::unique_lock<std::mutex> lock{_mtx};

    if(_count > 0)
    {
      _count--;
      return true;
    }

    return false;
  }

  void signal(std::size_t count = 1)
  {
    std::unique_lock<std::mutex> lock{_mtx};
    _count += count;
    while(count--)
    {
      _cv.notify_one();
    }
  }

private:
  std::mutex _mtx;
  std::condition_variable _cv;

  std::size_t _count;
};

