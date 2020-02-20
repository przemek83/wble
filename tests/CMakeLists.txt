project(tests)

file(GLOB SOURCES "*.cpp")
add_executable(tests ${SOURCES})

target_link_libraries(tests wble Qt5::Test Qt5::Core Qt5::Widgets)

add_test(NAME tests COMMAND tests)

