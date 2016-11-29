add_executable(11-producer-consumer
    11-producer-consumer.cpp
)

target_link_libraries(11-producer-consumer
    Threads::Threads
)

add_custom_target(run-11-producer-consumer
    DEPENDS 11-producer-consumer
    COMMAND ./11-producer-consumer
)

add_custom_target(run-10-all)
add_dependencies(run-10-all
    run-11-producer-consumer
)

add_dependencies(run-all
    run-10-all
)

