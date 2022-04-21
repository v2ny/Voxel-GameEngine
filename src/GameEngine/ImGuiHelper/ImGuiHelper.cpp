#include <ImGuiHelper.h>

void ImGuiHelper::ImGuiDefaultSettings(GLFWwindow* wind, const char* fontPath, const char* OpenGL3_glsl_version)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.WantCaptureMouse = true;

    ImGui::StyleColorsDark();

    io.Fonts->AddFontFromFileTTF(fontPath, 18.0f, NULL, NULL);

    ImGui_ImplGlfw_InitForOpenGL(wind, true);
    ImGui_ImplOpenGL3_Init(OpenGL3_glsl_version);
}

void ImGuiHelper::ImGuiRenderDD()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}