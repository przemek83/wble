project(examples)

set(SOURCES
    example.cpp
)

add_executable(examples ${SOURCES})

target_link_libraries(examples PRIVATE Qt6::Core Qt6::Widgets wble)

