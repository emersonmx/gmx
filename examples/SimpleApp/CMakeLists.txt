cmake_minimum_required(VERSION 2.6)

project(SimpleApp)

add_executable(${PROJECT_NAME}
    simple.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_PROJECT_NAME}
)
