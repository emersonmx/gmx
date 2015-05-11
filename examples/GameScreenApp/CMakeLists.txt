cmake_minimum_required(VERSION 2.6)

project(GameScreenApp)

add_executable(${PROJECT_NAME}
    game_screen.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_PROJECT_NAME}
)
