cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)
project(PropertyEditor LANGUAGES CXX C VERSION 1.0.4)

set(BUILD_VERSION "1" CACHE STRING "Build version")
set(BUILD_STATIC OFF CACHE BOOL "Enable static build")
set(DEV_BUILD OFF CACHE BOOL "Enable developer build")

set(CMAKE_CXX_STANDARD 17)

if(BUILD_STATIC)
    set(HelperLibrary_BUILD_STATIC ON)
    set(PropertyBrowser3_BUILD_STATIC ON)
    add_definitions(-DSTATIC)
endif()

if(BUILD_TESTS)
    enable_testing()
endif()

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Xml)

include(PropertyEditorDemo/cmake/appFlags.cmake)

list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/PropertyEditorDemo/cmake
)

include(commonTools)

add_subdirectory(libPropertyEditor)
add_subdirectory(PropertyEditorDemo)

if(NOT BUILD_STATIC)
    deployTargets(MAINTARGET PropertyEditorDemo TARGETS PropertyEditor)
else()
    deployTargets(MAINTARGET PropertyEditorDemo)
endif()





