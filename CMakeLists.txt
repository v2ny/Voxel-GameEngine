cmake_minimum_required(VERSION 3.0.0)
project(Voxel-GameEngine VERSION 1.0.0)

include(CTest)
enable_testing()

set(EXECUTABLE_CLASSES src/main.cpp src/pub/Utilities/Classes/BoxLogger.cpp src/pub/Utilities/Classes/floatsToRGB.cpp src/pub/Shaders/ShaderClass.cpp src/pub/Shaders/Organizing/VBO/VBO.cpp src/pub/Shaders/Organizing/VAO/VAO.cpp src/pub/Shaders/Organizing/EBO/EBO.cpp)
set(EXECUTABLE_NAME Voxel-GameEngine)
set(CUSTOM_BUILD_DEST program_build)
set(CUSTOM_TARGET_SHADERS incl_shaders)

add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_CLASSES})

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

target_link_libraries(${EXECUTABLE_NAME} glfw)
target_link_libraries(${EXECUTABLE_NAME} glad)

find_package(OpenGL REQUIRED)

target_link_libraries(${EXECUTABLE_NAME} OpenGL::GL)

add_custom_target(${CUSTOM_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CUSTOM_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CUSTOM_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXECUTABLE_NAME}.exe ${CUSTOM_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E copy_directory Libraries ${CUSTOM_BUILD_DEST}/lib
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/pub/Shaders/Source/ ${CUSTOM_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}
    COMMAND ${CMAKE_COMMAND} -E rename ${CUSTOM_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}/VertexShader.glsl ${CUSTOM_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}/vrtx.s.obj
    COMMAND ${CMAKE_COMMAND} -E rename ${CUSTOM_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}/FragmentShader.glsl ${CUSTOM_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}/frgmnt.s.obj
)

add_dependencies(${EXECUTABLE_NAME} ${CUSTOM_BUILD_DEST})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
