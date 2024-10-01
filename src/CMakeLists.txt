cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)
project(PropertyEditor LANGUAGES CXX C VERSION 1.0.4)

set(BUILD_VERSION "1" CACHE STRING "Build version")
set(CMAKE_CXX_STANDARD 17)

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

deployTargets(MAINTARGET PropertyEditorDemo)





