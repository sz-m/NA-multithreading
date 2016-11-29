#include <catch.hpp>

#include "bounded_queue.h"

#include <thread>

TEST_CASE("bounded_queue", "[bounded_queue]")
{
    bounded_queue<int, 4> queue;

    std::thread producer{
        [&](){
            for (int i = 0; i < 10; ++i)
            {
                queue.push_back(i);
            }
        }
    };

    std::thread consumer{
        [&](){
            for (int i = 0; i < 10; ++i)
            {
                auto x = queue.pop_front();
                REQUIRE(x == i);
            }
        }
    };

    producer.join();
    consumer.join();
}

TEST_CASE("delayed insertion", "[bounded_queue]")
{
    bounded_queue<int, 4> queue;

    std::thread producer{
        [&](){
            for (int i = 0; i < 10; ++i)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                queue.push_back(i);
            }
        }
    };

    std::thread consumer{
        [&](){
            for (int i = 0; i < 10; ++i)
            {
                auto x = queue.pop_front();
                REQUIRE(x == i);
            }
        }
    };

    producer.join();
    consumer.join();
}

TEST_CASE("delayed removal", "[bounded_queue]")
{
    bounded_queue<int, 4> queue;

    std::thread producer{
        [&](){
            for (int i = 0; i < 10; ++i)
            {
                queue.push_back(i);
            }
        }
    };

    std::thread consumer{
        [&](){
            for (int i = 0; i < 10; ++i)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                auto x = queue.pop_front();
                REQUIRE(x == i);
            }
        }
    };

    producer.join();
    consumer.join();
}

