cmake_minimum_required(VERSION 2.6)

project(gmx)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
endif (CMAKE_COMPILER_IS_GNUCC)
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
endif (CMAKE_COMPILER_IS_GNUCXX)

option (BUILD_EXAMPLES
    "Build examples" ON)

include_directories(${PROJECT_SOURCE_DIR})

add_library(${PROJECT_NAME}
    gmx/application.cpp
    gmx/game.cpp
    gmx/loaders.cpp
)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif (BUILD_EXAMPLES)
