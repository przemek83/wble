cmake_minimum_required(VERSION 3.5)

project(wble LANGUAGES CXX VERSION 0.0.1 DESCRIPTION "Library of usefull Qt widgets")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(wble SHARED
  src/wble_global.h
  src/DoubleSlider.cpp
  src/DoubleSlider.h
)

set_target_properties(wble PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(wble PROPERTIES SOVERSION 1)

set_property(TARGET wble PROPERTY PUBLIC_HEADER src/DoubleSlider.h src/wble_global.h)
target_include_directories(wble PRIVATE src)
include(GNUInstallDirs)

target_link_libraries(wble PRIVATE Qt5::Widgets)

target_compile_definitions(wble PRIVATE WBLE_LIBRARY)

install(TARGETS wble
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
