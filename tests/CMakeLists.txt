project(tests)

set(${PROJECT_NAME}_SOURCES
    Tests.cpp
    DoubleSliderTest.cpp
    DoubleSliderTest.h
    FilterDatesTest.cpp
    FilterDatesTest.h
    FilterStringsTest.cpp
    FilterStringsTest.h
    FilterIntegersTest.cpp
    FilterIntegersTest.h
    FilterDoublesTest.cpp
    FilterDoublesTest.h
    FilterNumbersCommon.cpp
    FilterNumbersCommon.h
    )

add_executable(tests ${${PROJECT_NAME}_SOURCES})

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tests wble Qt5::Test Qt5::Core Qt5::Widgets)

add_test(NAME tests COMMAND tests)

