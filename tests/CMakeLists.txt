SET(PROJECT_TESTS ${PROJECT_NAME}-tests)

set(${PROJECT_TESTS}_SOURCES
    Tests.cpp
    DoubleSliderTest.h
    DoubleSliderTest.cpp
    FilterDatesTest.h
    FilterDatesTest.cpp
    FilterStringsTest.h
    FilterStringsTest.cpp
    FilterIntegersTest.h
    FilterIntegersTest.cpp
    FilterDoublesTest.h
    FilterDoublesTest.cpp
    FilterNumbersCommon.h
    FilterNumbersCommon.cpp
    ProgressBarCounterTest.h
    ProgressBarCounterTest.cpp
    ProgressBarCommon.h
    ProgressBarCommon.cpp
    ProgressBarInfiniteTest.h
    ProgressBarInfiniteTest.cpp
)

qt_add_resources(${PROJECT_TESTS}_SOURCES testResources.qrc)

add_executable(${PROJECT_TESTS} ${${PROJECT_TESTS}_SOURCES})

target_link_libraries(${PROJECT_TESTS} PRIVATE wble Qt6::Core Qt6::Widgets Qt6::Test)

add_test(NAME ${PROJECT_TESTS} COMMAND ${PROJECT_TESTS})

