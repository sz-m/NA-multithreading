add_definitions(
    -fsanitize=thread
)

add_executable(31-spinlock
    31-spinlock.cpp
)

target_link_libraries(31-spinlock
    Threads::Threads
    -fsanitize=thread
)

add_custom_target(run-31-spinlock
    DEPENDS 31-spinlock
    COMMAND ./31-spinlock
)

add_custom_target(run-30-all)
add_dependencies(run-30-all
    run-31-spinlock
)

add_dependencies(run-all
    run-30-all
)

