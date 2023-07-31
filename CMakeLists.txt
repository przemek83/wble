cmake_minimum_required(VERSION 3.16)

project(wble
        LANGUAGES CXX
        VERSION 1.1.0
        DESCRIPTION "Library of useful Qt widgets"
        HOMEPAGE_URL "https://github.com/przemek83/wble")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Test)
qt_standard_project_setup()

set(SOURCES
    src/DoubleSlider.cpp
    src/Filter.cpp
    src/FilterStrings.cpp
    src/FilterDates.cpp
    src/FilterNumbers.cpp
    src/FilterIntegers.cpp
    src/FilterDoubles.cpp
    src/Utilities.cpp
    src/DoubleClickEater.cpp
    src/ProgressBar.cpp
    src/ProgressBarInfinite.cpp
    src/ProgressBarCounter.cpp
)

set(HEADERS
    src/wble_global.h
    src/DoubleSlider.h
    src/Filter.h
    src/FilterStrings.h
    src/FilterDates.h
    src/FilterNumbers.h
    src/FilterIntegers.h
    src/FilterDoubles.h
    src/Utilities.h
    src/DoubleClickEater.h
    src/ProgressBar.h
    src/ProgressBarInfinite.h
    src/ProgressBarCounter.h
 )

set(UI
    src/FilterStrings.ui
    src/FilterDates.ui
    src/FilterNumbers.ui
)
source_group("UI Files" FILES ${UI})

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${UI})

set(PUBLIC_HEADERS
    src/wble_global.h
    src/DoubleSlider.h
    src/Filter.h
    src/FilterStrings.h
    src/FilterDates.h
    src/FilterNumbers.h
    src/FilterIntegers.h
    src/FilterDoubles.h
    src/ProgressBar.h
    src/ProgressBarInfinite.h
    src/ProgressBarCounter.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${PUBLIC_HEADERS}"
)

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)

target_compile_definitions(${PROJECT_NAME} PRIVATE WBLE_LIBRARY)

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_subdirectory(examples)

enable_testing()
add_subdirectory(tests)


