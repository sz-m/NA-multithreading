#pragma once

#include <atomic>

template<typename T>
class counted_ptr
{
public:
    counted_ptr() = default;
    
    counted_ptr(T * ptr) : _state{ new _shared_state{ptr} }, _cache{ ptr }
    {}

    counted_ptr(const counted_ptr & other)
    {
      _state = other._state;
      _cache = other._cache;

      _acquire();
    }

    
    counted_ptr(counted_ptr && other)
    {
      _state = other._state;
      _cache = other._cache;

      other._state = nullptr;
      other._cache = nullptr;
    }
    
    counted_ptr & operator=(const counted_ptr & other)
    {
      _release();

      _state = other._state;
      _cache = other._cache;

      _acquire();
      
      return *this;
    }
    
    counted_ptr & operator=(counted_ptr && other)
    {
      _release();

      _state = other._state;
      _cache = other._cache;
      other._state = nullptr;
      other._cache = nullptr;

      return *this;
    }
    
    ~counted_ptr()
    {
      _release();
    }

    void reset(T * ptr = nullptr)
    {
      _release();

      if(!ptr)
      {
        _state = nullptr;
        _cache = nullptr;
      }
      
      _state = new _shared_state{ptr};
      _cache = ptr;

    }
    
    T * get() const
    {
      return _cache;
    }

    std::size_t use_count() const
    {
      if(!_state)
        return 0;

      return _state->count;
    }

private:
    struct _shared_state
    {
      T* ptr;
      std::atomic<std::size_t> count{ 1 };
    };

    _shared_state * _state = nullptr;
    T* _cache = nullptr;

    void _acquire()
    {
      if(_state)
      {
        _state->count++;
      }
    }
    
    void _release()
    {
      if(_state)
      {
        if(!--_state->count)
        {
          delete _state->ptr;
          delete _state;
        }
      }
    }
};

