cmake_minimum_required(VERSION 2.6)

project(SDLHelloApp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
set(EXTRA_LIBS ${EXTRA_LIBS} ${SDL2_LIBRARY})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
set(EXTRA_LIBS ${EXTRA_LIBS} ${SDL2_IMAGE_LIBRARY})

add_executable(${PROJECT_NAME}
    sdlhello.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_PROJECT_NAME}
    ${EXTRA_LIBS}
)
