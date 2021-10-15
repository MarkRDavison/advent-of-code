cmake_minimum_required(VERSION 3.10)

project(main)

set(SOURCES 
  src/main.cpp
) 

#set(HEADERS src/lib.hpp)
			
add_executable(main ${SOURCES} ${HEADERS})

set_property(TARGET main PROPERTY CXX_STANDARD 17)
set_property(TARGET main PROPERTY CXX_STANDARD_REQUIRED ON)

