cmake_minimum_required(VERSION 2.6)

# CMake Config
include(FindPkgConfig)

# Projects
project(gmx)

### Configs
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
endif (CMAKE_COMPILER_IS_GNUCC)
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
endif (CMAKE_COMPILER_IS_GNUCXX)

### Include paths
###### Project
include_directories(${PROJECT_SOURCE_DIR})

###### SDL2
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

###### SDL Image 2
pkg_search_module(SDL2_image REQUIRED SDL2_image)
include_directories(${SDL2_image_INCLUDE_DIRS})
set(EXTRA_LIBS ${EXTRA_LIBS} ${SDL2_image_LIBRARIES})

add_library(gmx
    Application.cpp
    Game.cpp
    Utils.cpp
)
