#pragma once

class spinlock
{
public:
    void lock();
    bool try_lock();
    void unlock();
};

