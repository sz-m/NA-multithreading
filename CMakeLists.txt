cmake_minimum_required(VERSION 3.5)

project(multithreading-examples CXX)

add_definitions(-DCATCH_CONFIG_MAIN)
add_definitions(-std=c++1z -Wall -Wextra -Wpedantic -Werror -Wfatal-errors)
include_directories(vendor SYSTEM)

find_package(Threads)

add_custom_target(run-all)

add_subdirectory(10-bounded-queue)
add_subdirectory(20-semaphore)
add_subdirectory(30-spinlock)
add_subdirectory(40-ptr)

