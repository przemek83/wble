project(examples)

file(GLOB SOURCES "*.cpp")
add_executable(examples ${SOURCES})

target_link_libraries(examples PRIVATE Qt5::Core Qt5::Widgets wble)

