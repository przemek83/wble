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

set_target_properties(wble PROPERTIES PUBLIC_HEADER include/DoubleSlider.h)
target_include_directories(wble PRIVATE src)
include(GNUInstallDirs)

#set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE PATH "Installation directory for executables")
#set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Installation directory for libraries")
#set(INSTALL_INC_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Installation directory for headers")

#install(TARGETS wble
#        RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
#        ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
#        LIBRARY DESTINATION "${INSTALL_LIB_DIR}" )

#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

target_link_libraries(wble PRIVATE Qt5::Widgets)

target_compile_definitions(wble PRIVATE WBLE_LIBRARY)

install(TARGETS wble
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
