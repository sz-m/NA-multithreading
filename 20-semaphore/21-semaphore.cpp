#include <catch.hpp>

#include "semaphore.h"

#include <atomic>
#include <thread>

TEST_CASE("construction", "[semaphore]")
{
    {
        semaphore sem{ 0 };
        REQUIRE(!sem.try_wait());
    }

    {
        semaphore sem{ 17 };
        REQUIRE(sem.try_wait());
    }
}

TEST_CASE("signal and wait", "[semaphore]")
{
    semaphore sem{ 0 };
    std::atomic<bool> flag{ false };

    std::thread t1{ [&](){
        sem.wait();
        REQUIRE(flag == true);
    } };

    flag = true;
    sem.signal();

    t1.join();
}

TEST_CASE("signal many", "[semaphore]")
{
    semaphore sem{ 0 };
    std::atomic<int> i{ 0 };

    std::thread t1{ [&](){
        sem.wait();
        sem.wait();

        REQUIRE(i > 1);

        sem.wait();
        sem.wait();

        REQUIRE(i == 2);
    } };

    ++i;
    sem.signal(2);
    ++i;
    sem.signal(2);

    t1.join();
}

