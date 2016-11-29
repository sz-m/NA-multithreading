#pragma once

template<typename T>
class counted_ptr
{
public:
    counted_ptr();
    counted_ptr(T * ptr);
    counted_ptr(const counted_ptr & other);
    counted_ptr(counted_ptr && other);
    counted_ptr & operator=(const counted_ptr & other);
    counted_ptr & operator=(counted_ptr && other);
    ~counted_ptr();

    void reset(T * ptr = nullptr);
    T * get() const;
    std::size_t use_count() const;

private:
    struct _shared_state;
    _shared_state * _state = nullptr;

    void _acquire();
    void _release();
};

