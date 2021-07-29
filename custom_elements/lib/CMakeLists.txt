cmake_minimum_required(VERSION 3.7.2...3.15.0)


# sources and resources
set(CUSTOM_ELEMENTS_SOURCES
    src/custom_elements/graph.cpp
)

set(CUSTOM_ELEMENTS_HEADERS
    include/custom_elements.hpp
    include/custom_elements/graph.hpp
)

set(ELEMENT_LIB_PATH ${ELEMENT_ROOT}/lib)
if (APPLE)
   set(ELEMENTS_HOST
      ${ELEMENT_LIB_PATH}/host/macos/app.mm
      ${ELEMENT_LIB_PATH}/host/macos/base_view.mm
      ${ELEMENT_LIB_PATH}/host/macos/key.mm
      ${ELEMENT_LIB_PATH}/host/macos/window.mm
   )
elseif (ELEMENTS_HOST_UI_LIBRARY STREQUAL "gtk")
   set(ELEMENTS_HOST
      ${ELEMENT_LIB_PATH}/host/linux/app.cpp
      ${ELEMENT_LIB_PATH}/host/linux/base_view.cpp
      ${ELEMENT_LIB_PATH}/host/linux/key.cpp
      ${ELEMENT_LIB_PATH}/host/linux/window.cpp
   )
elseif (WIN32)
   set(ELEMENTS_HOST
      ${ELEMENT_LIB_PATH}/host/windows/utils.hpp
      ${ELEMENT_LIB_PATH}/host/windows/app.cpp
      ${ELEMENT_LIB_PATH}/host/windows/base_view.cpp
      ${ELEMENT_LIB_PATH}/host/windows/key.cpp
      ${ELEMENT_LIB_PATH}/host/windows/window.cpp
   )
endif()

source_group("Source Files\\custom_elements"
   FILES
   ${CUSTOM_ELEMENTS_SOURCES}
)
source_group("Source Files\\elements_host"
   FILES
   ${ELEMENTS_HOST}
)
source_group("Header Files\\custom_elements"
   FILES
   ${CUSTOM_ELEMENTS_HEADERS}
)

add_library(custom_elements)

target_sources(custom_elements
    PRIVATE ${CUSTOM_ELEMENTS_SOURCES} ${ELEMENT_HOST}
    PUBLIC ${CUSTOM_ELEMENTS_HEADERS}
)

target_include_directories(custom_elements PUBLIC include )
target_link_libraries(custom_elements PUBLIC elements)
target_compile_features(custom_elements PUBLIC cxx_std_17)

if(ELEMENTS_ENABLE_LTO)
   set_target_properties(custom_elements PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if (NOT MSVC)
   find_package(PkgConfig REQUIRED)
endif()

###############################################################################
# Get rid of certain warnings, and make msvc support utf-8 without adding bom

target_compile_options(custom_elements PRIVATE
   $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -ftemplate-backtrace-limit=0>
   $<$<CXX_COMPILER_ID:Clang>:-Wall -Wpedantic -ftemplate-backtrace-limit=0>
   $<$<CXX_COMPILER_ID:AppleClang>:-Wall -Wpedantic -ftemplate-backtrace-limit=0>
   $<$<CXX_COMPILER_ID:MSVC>:/W4 /wd4244 /wd4305 /wd4996 /wd4267 /wd4018 /wd4456 /utf-8>
)

if (MSVC)
   # Kinda silly to have to do this: https://bit.ly/2ZXjzzn
   STRING(REGEX REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif()

if (APPLE)
   # Not sure why APPLE is not picking the target_compile_options above
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -ftemplate-backtrace-limit=0")
endif()

if (APPLE)
   set(lib_dir "/usr/local/opt")
endif()



###############################################################################
# Cairo

if (MSVC)
   target_include_directories(custom_elements PUBLIC ${ELEMENT_ROOT}/lib/external/cairo/include)

   if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      target_link_libraries(custom_elements PUBLIC ${ELEMENT_ROOT}/lib/external/cairo/lib/x64/cairo.lib)
   else()
	  target_link_libraries(custom_elements PUBLIC ${ELEMENT_ROOT}/lib/external/cairo/lib/x86/cairo.lib)
   endif()
elseif (APPLE)
	# TODO: add a min version specifiction
	pkg_check_modules(cairo REQUIRED IMPORTED_TARGET cairo)
   target_include_directories(custom_elements PUBLIC ${cairo_INCLUDE_DIRS})
   target_link_libraries(custom_elements PUBLIC "${lib_dir}/cairo/lib/libcairo.a")            # Static link
   target_link_libraries(custom_elements PRIVATE "${lib_dir}/libpng/lib/libpng.a")            # Static link
   target_link_libraries(custom_elements PRIVATE "${lib_dir}/pixman/lib/libpixman-1.a")       # Static link
   target_link_libraries(custom_elements PRIVATE "${lib_dir}/zlib/lib/libz.a")                # Static link
else()
	# TODO: add a min version specifiction
	pkg_check_modules(cairo REQUIRED IMPORTED_TARGET cairo)
	target_link_libraries(custom_elements PUBLIC PkgConfig::cairo)
endif()

###############################################################################
# Fontconfig

if (MSVC)
   target_include_directories(custom_elements PUBLIC ${ELEMENT_ROOT}/lib/external/fontconfig/include)

   if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	  target_link_libraries(custom_elements PUBLIC ${ELEMENT_ROOT}/lib/external/fontconfig/x64/fontconfig.lib)
   else()
	  target_link_libraries(custom_elements PUBLIC ${ELEMENT_ROOT}/lib/external/fontconfig/x86/fontconfig.lib)
   endif()
elseif (APPLE)
   pkg_check_modules(fontconfig REQUIRED IMPORTED_TARGET fontconfig)
   target_include_directories(custom_elements PUBLIC ${fontconfig_INCLUDE_DIRS})
   target_link_libraries(custom_elements PUBLIC "${lib_dir}/fontconfig/lib/libfontconfig.a")  # Static link
   target_link_libraries(custom_elements PUBLIC "${lib_dir}/expat/lib/libexpat.a")            # Static link
else()
   pkg_check_modules(fontconfig REQUIRED IMPORTED_TARGET fontconfig)
   target_link_libraries(custom_elements PUBLIC PkgConfig::fontconfig)
endif()

###############################################################################
# Freetype

if (MSVC)
   target_include_directories(custom_elements PUBLIC ${ELEMENT_ROOT}/lib/external/freetype/include)

   if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	  target_link_libraries(custom_elements PUBLIC ${ELEMENT_ROOT}/lib/external/freetype/win64/freetype.lib)
   else()
	  target_link_libraries(custom_elements PUBLIC ${ELEMENT_ROOT}/lib/external/freetype/win32/freetype.lib)
   endif()
elseif (APPLE)
   pkg_check_modules(freetype2 REQUIRED IMPORTED_TARGET freetype2)
   target_include_directories(custom_elements PUBLIC ${freetype2_INCLUDE_DIRS})
   target_link_libraries(custom_elements PUBLIC "${lib_dir}/freetype2/lib/libfreetype.a")     # Static link
   target_link_libraries(custom_elements PUBLIC "${lib_dir}/bzip2/lib/libbz2.a")              # Static link
elseif (UNIX OR WIN32)
   pkg_check_modules(freetype2 REQUIRED IMPORTED_TARGET freetype2)
   target_link_libraries(custom_elements PUBLIC PkgConfig::freetype2)
endif()

###############################################################################
# GTK (linux only)

if (ELEMENTS_HOST_UI_LIBRARY STREQUAL "gtk")
   pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)
   target_link_libraries(custom_elements PRIVATE PkgConfig::GTK3)
endif()

###############################################################################
# Asio headers
target_include_directories(custom_elements PUBLIC ${ELEMENT_ROOT}/lib/external/asio/asio/include)

###############################################################################
# Global options

if (APPLE)
   target_compile_definitions(custom_elements PRIVATE
      ELEMENTS_CLASS_PREFIX=${ELEMENTS_CLASS_PREFIX}
   )
   target_compile_options(custom_elements PUBLIC "-fobjc-arc")
elseif (WIN32)
   target_compile_definitions(custom_elements PUBLIC
      WIN32_LEAN_AND_MEAN
      NOMINMAX
      _UNICODE
      BOOST_DATE_TIME_NO_LIB
      BOOST_REGEX_NO_LIB
   )
endif()

if(ELEMENTS_HOST_UI_LIBRARY STREQUAL "gtk")
    target_compile_definitions(custom_elements PUBLIC ELEMENTS_HOST_UI_LIBRARY_GTK)
elseif(ELEMENTS_HOST_UI_LIBRARY STREQUAL "cocoa")
    if(NOT APPLE)
        message(FATAL_ERROR "Only macOS supports ELEMENTS_HOST_UI_LIBRARY=cocoa")
    endif()
    target_compile_definitions(custom_elements PUBLIC ELEMENTS_HOST_UI_LIBRARY_COCOA)
elseif(ELEMENTS_HOST_UI_LIBRARY STREQUAL "win32")
    if(NOT WIN32)
        message(FATAL_ERROR "Only Windows supports ELEMENTS_HOST_UI_LIBRARY=win32")
    endif()
    target_compile_definitions(custom_elements PUBLIC ELEMENTS_HOST_UI_LIBRARY_WIN32)
    if(ELEMENTS_HOST_ONLY_WIN7)
        target_compile_definitions(custom_elements PRIVATE ELEMENTS_HOST_ONLY_WIN7)
        message(STATUS "Windows 7 compatibility enabled")
    endif()
else()
    message(FATAL_ERROR "Invalid ELEMENTS_HOST_UI_LIBRARY=${ELEMENTS_HOST_UI_LIBRARY}. Set gtk, cocoa or win32.")
endif()

###############################################################################
# Libraries and linking

if (UNIX OR (WIN32 AND NOT MSVC))
   find_package(Threads)
   target_link_libraries(custom_elements PUBLIC Threads::Threads)
endif()

# ASIO requires this
if (WIN32 AND NOT MSVC)
   target_link_libraries(custom_elements PUBLIC ws2_32)
endif()

# Replace missing Shcore library removed by WIN32_LEAN_AND_MEAN
if (WIN32)
   target_link_libraries(custom_elements PUBLIC Shcore)
endif()

add_library(blf::custom_elements ALIAS custom_elements)
