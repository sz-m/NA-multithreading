#include <catch.hpp>

#include "counted_ptr.h"

#include <thread>

TEST_CASE("counted_ptr null construction", "[counted_ptr]")
{
    counted_ptr<int> ptr;
    REQUIRE(ptr.get() == nullptr);
    REQUIRE(ptr.use_count() == 0);
}

TEST_CASE("counted_ptr race free check", "[counted_ptr]")
{
    counted_ptr<int> ptr = new int;

    REQUIRE(ptr.use_count() == 1);

    auto routine = [&](){
        for (int i = 0; i < 100; ++i)
        {
            volatile auto copy = ptr;
        }
    };

    std::vector<std::thread> threads;
    threads.reserve(16);

    for (int i = 0; i < 16; ++i)
    {
        threads.emplace_back(routine);
    }

    for (auto && thread : threads)
    {
        thread.join();
    }

    REQUIRE(ptr.use_count() == 1);
}

