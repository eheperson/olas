cmake_minimum_required(VERSION 3.13.4)

# name and version of our project
project(OLAS VERSION 1.0)

configure_file(OLASConfig.h.in OLASConfig.h)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

# add another folder with another cmake
add_subdirectory(Adder)

# --- Download and Update all the submodules
# git submodule update --init --recursive cmakelists alternative 
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()
#
#--------------------------------------------------------------------
# Check the submodule Module
if(NOT EXISTS "external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()
# add the submodule directory
add_subdirectory(external/glfw)

# when including : <Adder/adder.h> >>> <adder.h>
target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC Adder
    PUBLIC external/glfw/include()    
) 

# where our libraries is gonna be
# 'Adder' is pathing from our build folder base
# base build folder is at after -B "cmake -S . -B ./out/build"
target_link_directories(
    ${PROJECT_NAME} 
    PRIVATE Adder
    PRIVATE external/glfw/src
)

# link the library to our project
target_link_libraries(
    ${PROJECT_NAME} 
    adder
    glfw
)
