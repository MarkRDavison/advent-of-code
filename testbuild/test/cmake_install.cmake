# Install script for directory: F:/Workspace/Git/advent-of-code/test

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/AdventOfCode")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("F:/Workspace/Git/advent-of-code/testbuild/test/Core/cmake_install.cmake")
  include("F:/Workspace/Git/advent-of-code/testbuild/test/2015/cmake_install.cmake")
  include("F:/Workspace/Git/advent-of-code/testbuild/test/2016/cmake_install.cmake")
  include("F:/Workspace/Git/advent-of-code/testbuild/test/2017/cmake_install.cmake")
  include("F:/Workspace/Git/advent-of-code/testbuild/test/2018/cmake_install.cmake")
  include("F:/Workspace/Git/advent-of-code/testbuild/test/2019/cmake_install.cmake")
  include("F:/Workspace/Git/advent-of-code/testbuild/test/2020/cmake_install.cmake")
  include("F:/Workspace/Git/advent-of-code/testbuild/test/2021/cmake_install.cmake")
  include("F:/Workspace/Git/advent-of-code/testbuild/test/2022/cmake_install.cmake")
  include("F:/Workspace/Git/advent-of-code/testbuild/test/2023/cmake_install.cmake")

endif()

