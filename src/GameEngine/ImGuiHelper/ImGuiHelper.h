#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

class ImGuiHelper
{
    public:
        void ImGuiDefaultSettings(GLFWwindow* wind, const char* fontPath, const char* OpenGL3_glsl_version);
        void ImGuiRenderDD();
};
