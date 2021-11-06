SET(AppMain "advent-of-code")

ADD_EXECUTABLE(${AppMain} "main.cpp" )

SET_PROPERTY(TARGET ${AppMain} PROPERTY CXX_STANDARD 17)
SET_PROPERTY(TARGET ${AppMain} PROPERTY CXX_STANDARD_REQUIRED ON)
TARGET_LINK_LIBRARIES(${AppMain} PRIVATE advent-of-code-core)

target_link_libraries(${AppMain} PUBLIC ${CONAN_LIBS})

ADD_CUSTOM_COMMAND(TARGET ${AppMain} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:${AppMain}>/data)