cmake_minimum_required(VERSION 3.0.0)
project(Voxel-GameEngine VERSION 1.0.0)

include(CTest)
enable_testing()

set(EXECUTABLE_CLASSES src/main.cpp src/pub/Utilities/Classes/BoxLogger.cpp src/pub/Utilities/Classes/floatsToRGB.cpp src/pub/Shaders/ShaderClass.cpp src/pub/Shaders/Organizing/VBO/VBO.cpp src/pub/Shaders/Organizing/VAO/VAO.cpp src/pub/Shaders/Organizing/EBO/EBO.cpp)

add_executable(Voxel-GameEngine ${EXECUTABLE_CLASSES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(DEF_INCLUDE_DIR Libraries/include)
set(GLFW_INCLUDE_DIR Libraries/source/glfw/include)
set(GLAD_INCLUDE_DIR Libraries/source/glad-ogl-core/include)
set(INCLUDE_DIR_UTILITIES src/pub/Utilities/Headers)
set(INCLUDE_DIR_SHADERS src/pub/Shaders)
set(INCLUDE_ARGS ${DEF_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDE_DIR} ${INCLUDE_DIR_UTILITIES} ${INCLUDE_DIR_SHADERS})

include_directories(${INCLUDE_ARGS})

add_subdirectory(Libraries/source/glfw)
add_subdirectory(Libraries/source/glad-ogl-core)

target_link_libraries(Voxel-GameEngine glfw)
target_link_libraries(Voxel-GameEngine glad)

find_package(OpenGL REQUIRED)

target_link_libraries(Voxel-GameEngine OpenGL::GL)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
