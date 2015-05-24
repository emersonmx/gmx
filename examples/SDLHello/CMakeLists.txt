cmake_minimum_required(VERSION 2.6)

project(SDLHelloApp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
set(EXTRA_LIBS ${EXTRA_LIBS} ${SDL2_LIBRARIES})

add_executable(${PROJECT_NAME}
    sdlhello.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_PROJECT_NAME}
    ${EXTRA_LIBS}
)
