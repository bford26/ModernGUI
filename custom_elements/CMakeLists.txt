


cmake_minimum_required(VERSION 3.9.6...3.15.0)

project(custom_elements LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(ElementsConfigCommon)

option(CUSTOM_ELEMENTS_BUILD_EXAMPLES "build Elements library examples" OFF)

add_subdirectory(lib)

if (CUSTOM_ELEMENTS_BUILD_EXAMPLES)
   set(ELEMENTS_ROOT ${PROJECT_SOURCE_DIR})
   add_subdirectory(examples)
endif()
