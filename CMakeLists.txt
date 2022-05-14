cmake_minimum_required(VERSION 3.13.4)

# name and version of our project
project(OLAS VERSION 1.0)

# find_package(GLEW REQUIRED)
# # find_package needs config.cmake
# # if we download source code and build it, it may does not work

#  find library
find_library(
    myglew glew 
    NAMES glew2 GLEW GLEW2 
    # PATHS "${CMAKE_CURRENT_SOURCE_DIR}/glew"
    # PATH_SUFFIXES "lib/Release/x64" "lib/Release/x86"   
    DOC "glew library"
)
if(${myglew} STREQUAL myglew-NOTFOUND)
# if(NOT ${myglew})
    message(FATAL_ERROR "no glew, sad day")
else()
    message(STATUS "glew found! as ${myglew}")
    # list(APPEND EXTRA_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/glew/include")
    list(APPEND EXTRA_LIBS ${myglew})
endif()
#
find_library(myglu glu NAMES GLU DOC "glu library")
if(${myglu} STREQUAL myglu-NOTFOUND)
# if(NOT ${myglu})
    message(FATAL_ERROR "no glu, sad day")
else()
    message(STATUS "glu found! as ${myglu}")
endif()
#
find_library(mygl gl NAMES GL DOC "gl library")
if(${mygl} STREQUAL mygl-NOTFOUND)
# if(NOT ${mygl})
    message(FATAL_ERROR "no gl, sad day")
else()
    message(STATUS "gl found! as ${mygl}")
endif()


configure_file(OLASConfig.h.in OLASConfig.h)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

# optional library settings
option(USE_ADDER "A simple library for adding 2 floats." ON)

# adder use logic
if(USE_ADDER)
    message(STATUS "External Library adder ")
    add_definitions(-DUSE_ADDER)
    add_subdirectory(Adder)
    #
    list(APPEND EXTRA_LIB_DIRS "Adder")
    list(APPEND EXTRA_INCLUDE_DIRS "Adder") # or : "${PROJECT_SOURCE_DIR}/Adder"
    list(APPEND EXTRA_LINKS adder)
    # OR (1) ------------------------------------------------------------------
    # # when including : <Adder/adder.h> >>> <adder.h>
    # target_include_directories( 
        # ${PROJECT_NAME} 
        # PUBLIC Adder
    # ) 
    # # # where our libraries is gonna be
    # # # 'Adder' is pathing from our build folder base
    # # # base build folder is at after -B "cmake -S . -B ./out /build"
    # target_link_directories( 
        # ${PROJECT_NAME} 
        # PUBLIC Adder
    # )
    # link the library to our project
    # target_link_libraries(
    #     ${PROJECT_NAME} 
    #     adder
    # )
    # OR (1) ------------------------------------------------------------------

endif()

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
# Check the submodule Module
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submodules was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()
#
# add the submodule directory
add_subdirectory(external/glfw)
#
target_include_directories( 
    ${PROJECT_NAME} 
    PUBLIC external/glfw/include
    ${EXTRA_INCLUDE_DIRS}
) 
# #
target_link_directories( 
    ${PROJECT_NAME} 
    PUBLIC external/glfw/src
    ${EXTRA_LIB_DIR}
)
#
# link the library to our project
target_link_libraries(
    ${PROJECT_NAME} 
    glfw
    ${EXTRA_LINKS}
    # ${myglew}
    ${myglu}
    ${mygl}
)


# installing 
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/OLASConfig.h" DESTINATION include)

# Packing

# Options for packing
set(PACK_PACKAGE_VENDOR "eheperson")
set(CPACK_SYSTEM_NAME "enivicivokki")
set(PACKAGE_DIR "${CMAKE_SOURCE_DIR}/out/package")
set(CPACK_PACKAGE_DIRECTORY "${PACKAGE_DIR}")
#
# to distribute our project to other people 
# This module will include any runtime libraries that are needed by the project 
# for the current platform
include(InstallRequiredSystemLibraries)
#
# set some CPack variables to where we have stored the license and 
# version information for this project.
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "My funky project")
set(CPACK_PACKAGE_VENDOR ${CPACK_PACKAGE_VENDOR})
#
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
#
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_NAME_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_NAME_VERSION_MINOR}")
# #
set(CPACK_SOURCE_GENERATOR "TGZ")
# #
include(CPack)