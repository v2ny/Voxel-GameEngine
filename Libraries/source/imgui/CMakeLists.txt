cmake_minimum_required(VERSION 3.10)

# Project Name
project(ImGui)

# This cmake file try to make a lib of ImGui glfw backend
add_definitions(-fPIC)

set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

find_package(OpenGL REQUIRED)

# Get header and source file name
file(GLOB_RECURSE SOURCE_CPP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE SOURCE_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)

# create target
add_library(${PROJECT_NAME} STATIC ${SOURCE_CPP})
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL)
set_target_properties(${PROJECT_NAME} PROPERTIES IMPORTED_LINK_LIBRARIES "OpenGL::GL")
set_target_properties(${PROJECT_NAME} PROPERTIES INTERFACE_LINK_LIBRARIES "OpenGL::GL")
set(IMGUI_LIBRARIES ImGui;OpenGL::GL)

install(TARGETS ${PROJECT_NAME} 
    EXPORT ImGuiConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

export(TARGETS ${PROJECT_NAME}
FILE "${CMAKE_CURRENT_BINARY_DIR}/ImGuiConfig.cmake")

install(EXPORT ImGuiConfig
    DESTINATION lib/cmake/ImGui
    EXPORT_LINK_INTERFACE_LIBRARIES
)