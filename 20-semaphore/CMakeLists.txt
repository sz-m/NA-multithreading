add_executable(21-semaphore
    21-semaphore.cpp
)

target_link_libraries(21-semaphore
    Threads::Threads
)

add_custom_target(run-21-semaphore
    DEPENDS 21-semaphore
    COMMAND ./21-semaphore
)

add_custom_target(run-20-all)
add_dependencies(run-20-all
    run-21-semaphore
)

add_dependencies(run-all
    run-20-all
)

