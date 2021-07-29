cmake_minimum_required(VERSION 3.9.6...3.15.0)
project(ModernGUI LANGUAGES C CXX)

if (NOT ELEMENTS_ROOT)
   message(FATAL_ERROR "ELEMENTS_ROOT is not set")
endif()

# Make sure ELEMENTS_ROOT is an absolute path to add to the CMake module path
get_filename_component(ELEMENTS_ROOT "${ELEMENTS_ROOT}" ABSOLUTE)
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${ELEMENTS_ROOT}/cmake")

# If we are building outside the project, you need to set ELEMENTS_ROOT:
if (NOT ELEMENTS_BUILD_EXAMPLES)
   include(ElementsConfigCommon)
   set(ELEMENTS_BUILD_EXAMPLES OFF)
   add_subdirectory(${ELEMENTS_ROOT} elements)
   # message(STATUS "add subdir elements!")
endif()

# add our custom elements lib
add_subdirectory(${ELEMENTS_ROOT}/../custom_elements/ custom_elements)

set(ELEMENTS_APP_PROJECT "ModernGUI")
set(ELEMENTS_APP_TITLE "Modern GUI")
set(ELEMENTS_APP_COPYRIGHT "Copyright (c) 2016-2020 Joel de Guzman")
set(ELEMENTS_APP_ID "com.cycfi.mgui")
set(ELEMENTS_APP_VERSION "1.0")

# UNCOMMENT when resources actually required
# set(ELEMENTS_APP_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources/)

include(ElementsConfigApp)

target_link_libraries(${ELEMENTS_APP_PROJECT} PRIVATE custom_elements)
