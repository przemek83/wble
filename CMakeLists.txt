cmake_minimum_required(VERSION 3.16)

project(wble
        LANGUAGES CXX
        VERSION 1.1.0
        DESCRIPTION "Library of useful Qt widgets"
        HOMEPAGE_URL "https://github.com/przemek83/wble")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CODE_COVERAGE "Collect coverage" OFF)

if(CODE_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 --coverage")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Test)
qt_standard_project_setup()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(${PROJECT_NAME}_SOURCES 
    src/DoubleSlider.cpp
    src/Filter.cpp
    src/FilterStrings.cpp
    src/FilterDates.cpp
    src/FilterNumbers.cpp
    src/FilterIntegers.cpp
    src/FilterDoubles.cpp
    src/Utilities.h
    src/Utilities.cpp
    src/DoubleClickEater.h
    src/DoubleClickEater.cpp
    src/ProgressBar.cpp
    src/ProgressBarInfinite.cpp
    src/ProgressBarCounter.cpp
)

 set(PUBLIC_HEADERS
    include/${PROJECT_NAME}/wble_global.h
    include/${PROJECT_NAME}/DoubleSlider.h
    include/${PROJECT_NAME}/Filter.h
    include/${PROJECT_NAME}/FilterStrings.h
    include/${PROJECT_NAME}/FilterDates.h
    include/${PROJECT_NAME}/FilterNumbers.h
    include/${PROJECT_NAME}/FilterIntegers.h
    include/${PROJECT_NAME}/FilterDoubles.h
    include/${PROJECT_NAME}/ProgressBar.h
    include/${PROJECT_NAME}/ProgressBarInfinite.h
    include/${PROJECT_NAME}/ProgressBarCounter.h
)

set(UI
    src/FilterStrings.ui
    src/FilterDates.ui
    src/FilterNumbers.ui
)
source_group("UI Files" FILES ${UI})

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SOURCES} ${PUBLIC_HEADERS} ${UI})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  PRIVATE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${PUBLIC_HEADERS}")

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)

target_compile_definitions(${PROJECT_NAME} PRIVATE WBLE_LIBRARY)

install(TARGETS ${PROJECT_NAME} 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(examples)
    enable_testing()
    add_subdirectory(tests)
endif()
