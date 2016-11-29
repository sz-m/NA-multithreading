#include <catch.hpp>

#include "spinlock.h"

#include <mutex>
#include <thread>

TEST_CASE("try_lock", "[spinlock]")
{
    {
        spinlock mut;

        REQUIRE(mut.try_lock());
    }
}

TEST_CASE("lock unlock", "[spinlock]")
{
    {
        spinlock mut;
        int i = 0;

        auto routine = [&](){
            std::lock_guard<spinlock> lock{ mut };
            if (i < 3)
            {
                ++i;
            }
        };

        std::thread t1{ routine };
        std::thread t2{ routine };
        std::thread t3{ routine };
        std::thread t4{ routine };

        t1.join();
        t2.join();
        t3.join();
        t4.join();

        REQUIRE(i == 3);
    }
}

