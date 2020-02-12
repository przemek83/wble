cmake_minimum_required(VERSION 3.8)

project(wble LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "Library of usefull Qt widgets")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
add_definitions( ${QT_DEFINITIONS} )

add_library(wble SHARED
  src/wble_global.h
  src/DoubleSlider.cpp
  src/DoubleSlider.h
)

set_target_properties(wble PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(wble PROPERTIES SOVERSION 1)

set_property(TARGET wble PROPERTY PUBLIC_HEADER src/DoubleSlider.h src/wble_global.h)
target_include_directories(wble PUBLIC src)
include(GNUInstallDirs)

target_link_libraries(wble PRIVATE Qt5::Core Qt5::Widgets)

target_compile_definitions(wble PRIVATE WBLE_LIBRARY)

install(TARGETS wble
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

file(GLOB_RECURSE DLLS "${CMAKE_BINARY_DIR}/*.dll" )
file(COPY ${DLLS} DESTINATION ${CMAKE_BINARY_DIR}/examples)
file(COPY ${DLLS} DESTINATION ${CMAKE_BINARY_DIR}/tests)

add_subdirectory(examples)

enable_testing()
add_subdirectory(tests)
