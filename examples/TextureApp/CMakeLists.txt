cmake_minimum_required(VERSION 2.6)

project(TextureApp)

add_executable(${PROJECT_NAME}
    texture.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_PROJECT_NAME}
    ${EXTRA_LIBS}
)
