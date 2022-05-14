cmake_minimum_required(VERSION 3.13.4)

project(OLAS)

add_executable(${PROJECT_NAME} main.cpp)

# add another folder with another cmake
add_subdirectory(Adder)

# when including : <Adder/adder.h> >>> <adder.h>
target_include_directories(${PROJECT_NAME} PUBLIC Adder) 

# where our libraries is gonna be
# 'Adder' is pathing from our build folder base
# base build folder is at after -B "cmake -S . -B ./out/build"
target_link_directories(${PROJECT_NAME} PRIVATE Adder)

# link the library to our project
target_link_libraries(${PROJECT_NAME} adder)