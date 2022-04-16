cmake_minimum_required(VERSION 3.0.0)
project(Voxel-GameEngine VERSION 1.0.0)

include(CTest)
enable_testing()

add_executable(Voxel-GameEngine main.cpp floatsToRGB.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(Libraries/include/)

add_subdirectory(Libraries/source/glfw)
add_subdirectory(Libraries/source/glad-ogl-core)

target_link_libraries(Voxel-GameEngine glfw)
target_link_libraries(Voxel-GameEngine glad)

find_package(OpenGL REQUIRED)

target_link_libraries(Voxel-GameEngine OpenGL::GL)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
