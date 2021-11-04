cmake_minimum_required(VERSION 3.10)

project(main)

set(SOURCES 
  src/main.cpp
) 

include(${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
#set(HEADERS src/lib.hpp)
conan_basic_setup()

add_executable(main ${SOURCES} ${HEADERS})

set_property(TARGET main PROPERTY CXX_STANDARD 17)
set_property(TARGET main PROPERTY CXX_STANDARD_REQUIRED ON)


target_link_libraries(main
    PRIVATE ${CONAN_LIBS}
)