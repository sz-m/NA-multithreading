#pragma once

#include <cstddef>

template<typename T, std::size_t N>
class bounded_queue
{
public:
    void push_back(T t);
    T pop_front();
};
