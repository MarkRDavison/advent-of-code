CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

CMAKE_POLICY(SET CMP0074 NEW)
if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.19)
  CMAKE_POLICY(SET CMP0110 NEW)
endif()

set(CMAKE_DEBUG_POSTFIX "-d")

PROJECT(AdventOfCode 
	VERSION 1
	LANGUAGES CXX)
SET(AOC_CXX_STANDARD 20)
	
SET(CMAKE_CXX_STANDARD ${AOC_CXX_STANDARD})
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# https://github.com/conan-io/cmake-conan/issues/249
IF (CONAN_EXPORTED)
	MESSAGE(STATUS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
	INCLUDE(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
	conan_basic_setup(TARGETS)
ELSE()
    if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
		message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
	    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
		              "${CMAKE_BINARY_DIR}/conan.cmake"
					  EXPECTED_HASH SHA256=5cdb3042632da3efff558924eecefd580a0e786863a857ca097c3d1d43df5dcd
					  TLS_VERIFY ON)
    endif()
    include(${CMAKE_BINARY_DIR}/conan.cmake)
	conan_cmake_run(CONANFILE conanfile.txt BASIC_SETUP CMAKE_TARGETS KEEP_RPATHS BUILD missing)
ENDIF()


add_library("zeno-engine-interface" INTERFACE)
target_include_directories("zeno-engine-interface" INTERFACE ${CONAN_INCLUDE_DIRS_ZENO-ENGINE})
target_link_directories("zeno-engine-interface" INTERFACE ${CONAN_LIB_DIRS_ZENO-ENGINE})

IF (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_link_libraries("zeno-engine-interface" INTERFACE zeno-engine-utility-s-d)
	target_link_libraries("zeno-engine-interface" INTERFACE zeno-engine-core-s-d)	
ELSE(CMAKE_BUILD_TYPE STREQUAL "Release" ||
	 CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" ||
	 CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
	target_link_libraries("zeno-engine-interface" INTERFACE zeno-engine-utility-s)
	target_link_libraries("zeno-engine-interface" INTERFACE zeno-engine-core-s)
ENDIF()


SET(ADVENT_OF_CODE_CONAN_LIBS
	zeno-engine-interface
)

ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(app)
ENABLE_TESTING()
ADD_SUBDIRECTORY(test)