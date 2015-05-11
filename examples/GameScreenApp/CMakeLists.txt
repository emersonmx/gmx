cmake_minimum_required(VERSION 2.6)

# CMake Config
include(FindPkgConfig)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# Projects
project(GameScreenApp)

### Configs
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
endif (CMAKE_COMPILER_IS_GNUCC)
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmessage-length=0")
endif (CMAKE_COMPILER_IS_GNUCXX)

include_directories(${PROJECT_SOURCE_DIR})

find_package(FreeImage REQUIRED)
include_directories(${FREEIMAGE_INCLUDE_DIRS})
set(EXTRA_LIBS ${EXTRA_LIBS} ${FREEIMAGE_LIBRARIES})

add_executable(${PROJECT_NAME}
    game_screen.cpp
)

target_link_libraries(${PROJECT_NAME}
    gmx
)
