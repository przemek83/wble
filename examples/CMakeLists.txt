project(examples)

set(${PROJECT_NAME}_SOURCES
    example.cpp
    )

add_executable(examples ${${PROJECT_NAME}_SOURCES})

target_link_libraries(examples PRIVATE Qt5::Core Qt5::Widgets wble)

