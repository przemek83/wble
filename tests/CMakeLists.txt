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
    ProgressBarCounterTest.cpp
    ProgressBarCounterTest.h
    ProgressBarCommon.cpp
    ProgressBarCommon.h
    ProgressBarInfiniteTest.cpp
    ProgressBarInfiniteTest.h
    )

add_executable(tests ${${PROJECT_NAME}_SOURCES})

target_link_libraries(tests PRIVATE Qt5::Test Qt5::Core Qt5::Widgets wble)

add_test(NAME tests COMMAND tests)

