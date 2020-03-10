cmake_minimum_required(VERSION 3.8)

project(wble LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "Library of useful Qt widgets")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 COMPONENTS Widgets Core Test REQUIRED)
add_definitions( ${QT_DEFINITIONS} )

add_library(wble SHARED
  src/wble_global.h
  src/DoubleSlider.cpp
  src/DoubleSlider.h
  src/Filter.cpp
  src/Filter.h
  src/FilterStrings.cpp
  src/FilterStrings.h
  src/FilterStrings.ui
  src/FilterDates.cpp
  src/FilterDates.h
  src/FilterDates.ui
  src/FilterNumbers.cpp
  src/FilterNumbers.h
  src/FilterNumbers.ui
  src/FilterIntegers.cpp
  src/FilterIntegers.h
  src/FilterDoubles.cpp
  src/FilterDoubles.h
  src/Utilities.cpp
  src/Utilities.h
  src/DoubleClickEater.cpp
  src/DoubleClickEater.h
  src/ProgressBar.cpp
  src/ProgressBar.h
  src/ProgressBarInfinite.cpp
  src/ProgressBarInfinite.h
  src/ProgressBarCounter.cpp
  src/ProgressBarCounter.h
)

set_target_properties(wble PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(wble PROPERTIES SOVERSION 1)

set_property(TARGET wble PROPERTY PUBLIC_HEADER
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
    src/wble_global.h)
target_include_directories(wble PUBLIC src)
include(GNUInstallDirs)

target_link_libraries(wble PRIVATE Qt5::Core Qt5::Widgets)

target_compile_definitions(wble PRIVATE WBLE_LIBRARY)

add_custom_command(
        TARGET wble POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_BINARY_DIR}/libwble.dll
                ${CMAKE_BINARY_DIR}/examples/libwble.dll)

add_custom_command(
        TARGET wble POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_BINARY_DIR}/libwble.dll
                ${CMAKE_BINARY_DIR}/tests/libwble.dll)

install(TARGETS wble
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

add_subdirectory(examples)

enable_testing()
add_subdirectory(tests)


