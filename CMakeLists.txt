cmake_minimum_required(VERSION 3.20)
project(Voxel-GameEngine VERSION 1.0.0)

include(CTest)
enable_testing()

set(APPLICATION_PATH src/App)
set(GAME_ENGINE_PATH src/GameEngine)
set(PUB_UTILS_PATH src/pub/Utilities)
set(EXECUTABLE_CLASSES src/main.cpp ${PUB_UTILS_PATH}/Classes/BoxLogger.cpp 
    ${APPLICATION_PATH}/CustomMessageBox/CustomMessageBox.cpp ${PUB_UTILS_PATH}/Classes/floatsToRGB.cpp 
    ${GAME_ENGINE_PATH}/Shaders/ShaderClass.cpp ${GAME_ENGINE_PATH}/Shaders/Organizing/VBO/VBO.cpp 
    ${GAME_ENGINE_PATH}/Shaders/Organizing/VAO/VAO.cpp ${GAME_ENGINE_PATH}/Shaders/Organizing/EBO/EBO.cpp 
    ${GAME_ENGINE_PATH}/stb/stb.cpp ${GAME_ENGINE_PATH}/TextureClass/Texture.cpp 
    ${GAME_ENGINE_PATH}/ImGuiHelper/ImGuiHelper.cpp ${APPLICATION_PATH}/GUI/GUI.cpp 
    ${GAME_ENGINE_PATH}/CameraClass/Camera.cpp ${PUB_UTILS_PATH}/Classes/deltaTime.cpp 
    ${GAME_ENGINE_PATH}/MeshClass/Mesh.cpp)
set(EXECUTABLE_NAME Voxel-GameEngine)
set(DLL_CLASSES ${EXECUTABLE_CLASS} Libraries/source/glad-ogl-core/src/glad.c)
set(DLL_NAME ${EXECUTABLE_NAME}.r)
set(GLFW_LIB_DIR Libraries/source/glfw/src/)
set(CUSTOM_TARGET_SHADERS incl_shaders)
set(CUSTOM_BUILD_DEST program_build)
set(LIB_BUILD_DEST lib)
set(BIN_BUILD_DEST binaries)
set(PKGS_BUILD_DEST pkgs)

add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_CLASSES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "-fpermissive")
set(DEF_INCLUDE_DIR Libraries/include)
set(GLFW_INCLUDE_DIR Libraries/source/glfw/include)
set(GLAD_INCLUDE_DIR Libraries/source/glad-ogl-core/include)
set(IMGUI_INCLUDE_DIR Libraries/source/imgui)
set(IMGUI_LIBRARIES ImGui;glfw;OpenGL::GL)
set(STB_INCLUDE_DIR Libraries/include/stb)
set(PKGS_INCLUDE_DIR assets)
set(INCLUDE_DIR_IGH ${GAME_ENGINE_PATH}/ImGuiHelper)
set(INCLUDE_DIR_UTILITIES ${PUB_UTILS_PATH}/Headers)
set(INCLUDE_DIR_SHADERS ${GAME_ENGINE_PATH}/Shaders)
set(INCLUDE_DIR_CAMERA_CLASS ${GAME_ENGINE_PATH}/CameraClass)
set(INCLUDE_DIR_TEXTURES_CLASS ${GAME_ENGINE_PATH}/TextureClass)
set(INCLUDE_DIR_CUSTOM_MESSAGE_BOX ${APPLICATION_PATH}/CustomMessageBox)
set(INCLUDE_DIR_GUI_CLASS ${APPLICATION_PATH}/GUI)
set(INCLUDE_DIR_MESH_CLASS ${GAME_ENGINE_PATH}/MeshClass)
set(INCLUDE_ARGS ${DEF_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${GLAD_INCLUDE_DIR} ${INCLUDE_DIR_UTILITIES} ${INCLUDE_DIR_SHADERS} ${INCLUDE_DIR_CAMERA_CLASS} ${IMGUI_INCLUDE_DIR} ${INCLUDE_DIR_TEXTURES_CLASS} ${INCLUDE_DIR_IGH} ${INCLUDE_DIR_CUSTOM_MESSAGE_BOX} ${INCLUDE_DIR_GUI_CLASS} ${INCLUDE_DIR_MESH_CLASS})

include_directories(${INCLUDE_ARGS})

add_subdirectory(Libraries/source/glfw)
add_subdirectory(Libraries/source/glad-ogl-core)
add_subdirectory(Libraries/source/imgui)
add_subdirectory(Libraries/include/glm)

target_link_libraries(${EXECUTABLE_NAME} glfw glad glm)

find_package(OpenGL REQUIRED)
find_path(STB_INCLUDE_DIR "stb.h") 

target_include_directories(${EXECUTABLE_NAME} PRIVATE ${STB_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} OpenGL::GL ${IMGUI_LIBRARIES})

# If you are not seeing the exe file comment the add_custom_target & add_dependencies and type make or mingw32-make
# And wait until you see the exe file then uncomment and type make or mingw32-make again
# Then you can now run the program_build executable file without problems!
add_custom_target(${CUSTOM_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CUSTOM_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${PKGS_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${LIB_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${EXECUTABLE_NAME}.exe ${CUSTOM_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different lib${EXECUTABLE_NAME}.r.dll ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${LIB_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/DLLs/glfw3.dll ${CUSTOM_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/DLLs/libglad.dll ${CUSTOM_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/DLLs/imageres.dll ${CUSTOM_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different lib${EXECUTABLE_NAME}.r.dll ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${LIB_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E copy_directory Libraries ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${LIB_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${INCLUDE_DIR_SHADERS}/Source/ ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/DLLs/ ${CUSTOM_BUILD_DEST}/
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets/ ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${PKGS_BUILD_DEST}
    COMMAND ${CMAKE_COMMAND} -E rename ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${PKGS_BUILD_DEST}/imgs/github_img.png ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${PKGS_BUILD_DEST}/imgs/ghpng.img.obj
    COMMAND ${CMAKE_COMMAND} -E rename ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${PKGS_BUILD_DEST}/imgs/materials/Tiles/Tiles012_1K_Color.jpg ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${PKGS_BUILD_DEST}/imgs/materials/Tiles/tdiuse.img.obj
    COMMAND ${CMAKE_COMMAND} -E rename ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${PKGS_BUILD_DEST}/imgs/materials/Tiles/Tiles012_1K_Displacement.jpg ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${PKGS_BUILD_DEST}/imgs/materials/Tiles/tspec.img.obj
    COMMAND ${CMAKE_COMMAND} -E rename ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${PKGS_BUILD_DEST}/fonts/GeosansLight.ttf ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${PKGS_BUILD_DEST}/fonts/geosnsl.fnt.obj
    COMMAND ${CMAKE_COMMAND} -E rename ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${PKGS_BUILD_DEST}/fonts/LouisGeorgeCafeB_TYPE.ttf ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${PKGS_BUILD_DEST}/fonts/lgeorgecfeb.fnt.obj
    COMMAND ${CMAKE_COMMAND} -E rename ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${LIB_BUILD_DEST}/lib${EXECUTABLE_NAME}.r.dll ${CUSTOM_BUILD_DEST}/${EXECUTABLE_NAME}.dll
    COMMAND ${CMAKE_COMMAND} -E rename ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}/VertexShader.glsl ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}/vrtx.s.obj
    COMMAND ${CMAKE_COMMAND} -E rename ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}/FragmentShader.glsl ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}/frgmnt.s.obj
    COMMAND ${CMAKE_COMMAND} -E rename ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}/LightVertexShader.glsl ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}/lght.vrtx.s.obj
    COMMAND ${CMAKE_COMMAND} -E rename ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}/LightFragmentShader.glsl ${CUSTOM_BUILD_DEST}/${BIN_BUILD_DEST}/${CUSTOM_TARGET_SHADERS}/lght.frgmnt.s.obj
)

add_dependencies(${EXECUTABLE_NAME} ${CUSTOM_BUILD_DEST})

# If you did type make or mingw32-make and your changes didn't apply.
# type make or mingw32-make again and try to run it

add_library(${DLL_NAME} SHARED ${DLL_CLASSES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
