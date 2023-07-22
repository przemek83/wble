project(tests)

set(SOURCES
    Tests.cpp
    DoubleSliderTest.cpp
    FilterDatesTest.cpp
    FilterStringsTest.cpp
    FilterIntegersTest.cpp
    FilterDoublesTest.cpp
    FilterNumbersCommon.cpp
    ProgressBarCounterTest.cpp
    ProgressBarCommon.cpp
    ProgressBarInfiniteTest.cpp
)

set(HEADERS
    DoubleSliderTest.h
    FilterDatesTest.h
    FilterStringsTest.h
    FilterIntegersTest.h
    FilterDoublesTest.h
    FilterNumbersCommon.h
    ProgressBarCounterTest.h
    ProgressBarCommon.h
    ProgressBarInfiniteTest.h
 )

add_executable(tests ${SOURCES} ${HEADERS})

target_link_libraries(tests PRIVATE Qt6::Core Qt6::Widgets Qt6::Test wble)

add_test(NAME tests COMMAND tests)

