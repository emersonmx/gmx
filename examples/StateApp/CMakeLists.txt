cmake_minimum_required(VERSION 2.6)

project(StateApp)

add_executable(${PROJECT_NAME}
    stateapp.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_PROJECT_NAME}
)
