cmake_minimum_required(VERSION 2.6)

project(TextureApp)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
set(EXTRA_LIBS ${EXTRA_LIBS} ${OPENGL_LIBRARIES})

find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
set(EXTRA_LIBS ${EXTRA_LIBS} ${GLFW_LIBRARIES})

find_package(FreeImage REQUIRED)
include_directories(${FREEIMAGE_INCLUDE_DIRS})
set(EXTRA_LIBS ${EXTRA_LIBS} ${FREEIMAGE_LIBRARIES})

add_executable(${PROJECT_NAME}
    texture.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${CMAKE_PROJECT_NAME}
    ${EXTRA_LIBS}
)
