
set (SOURCES game.cpp main.cpp testcomponent.cpp)

add_executable(ExampleA ${SOURCES})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ExampleA MoleBox)

file(COPY Content/ DESTINATION ${CMAKE_BINARY_DIR})