add_definitions(
    -fsanitize=thread
)

add_executable(41-ptr
    41-ptr.cpp
)

target_link_libraries(41-ptr
    Threads::Threads
    -fsanitize=thread
)

add_custom_target(run-41-ptr
    DEPENDS 41-ptr
    COMMAND ./41-ptr
)

add_custom_target(run-40-all)
add_dependencies(run-40-all
    run-41-ptr
)

add_dependencies(run-all
    run-40-all
)

