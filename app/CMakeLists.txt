SET(AppMain "advent-of-code")

ADD_EXECUTABLE(${AppMain} "main.cpp" )

find_package (Threads REQUIRED)

SET_PROPERTY(TARGET ${AppMain} PROPERTY CXX_STANDARD ${AOC_CXX_STANDARD})
SET_PROPERTY(TARGET ${AppMain} PROPERTY CXX_STANDARD_REQUIRED ON)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-core)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2015)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2016)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2017)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2018)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2019)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2020)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2021)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2022)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-year2023)
target_link_libraries(${AppMain} PUBLIC Threads::Threads)

MESSAGE(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

foreach(liblib IN LISTS ADVENT_OF_CODE_CONAN_LIBS)
    MESSAGE(STATUS ${liblib})
	TARGET_LINK_LIBRARIES(${AppMain} PRIVATE ${liblib})
endforeach()

ADD_CUSTOM_COMMAND(TARGET ${AppMain} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${AppMain}>/data)