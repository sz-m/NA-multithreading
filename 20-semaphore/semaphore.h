#pragma once

#include <cstddef>

class semaphore
{
public:
    semaphore(std::size_t count);
    void wait();
    bool try_wait();
    void signal(std::size_t count = 1);
};

