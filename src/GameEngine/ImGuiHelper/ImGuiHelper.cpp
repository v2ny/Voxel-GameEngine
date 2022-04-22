#include <ImGuiHelper.h>

void ImGuiHelper::ImGuiDefaultSettings(GLFWwindow* wind, const char* fontPath, const char* OpenGL3_glsl_version)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle* style = &ImGui::GetStyle();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.WantCaptureMouse = true;

    io.Fonts->AddFontFromFileTTF(fontPath, 18.0f, NULL, NULL);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(46.0f / 255.0f, 47.0f / 255.0f, 53.0f / 255.0f, 1.0f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(66.0f / 255.0f, 67.0f / 255.0f, 73.0f / 255.0f, 1.0f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(46.0f / 255.0f, 47.0f / 255.0f, 53.0f / 255.0f, 1.0f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(46.0f / 255.0f, 47.0f / 255.0f, 53.0f / 255.0f, 1.0f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(66.0f / 255.0f, 67.0f / 255.0f, 73.0f / 255.0f, 1.0f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(76.0f / 255.0f, 77.0f / 255.0f, 83.0f / 255.0f, 1.0f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(36.0f / 255.0f, 37.0f / 255.0f, 43.0f / 255.0f, 1.0f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(46.0f / 255.0f, 47.0f / 255.0f, 53.0f / 255.0f, 1.0f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(46.0f / 255.0f, 47.0f / 255.0f, 53.0f / 255.0f, 1.0f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(46.0f / 255.0f, 47.0f / 255.0f, 53.0f / 255.0f, 1.0f);
    style->CellPadding = ImVec2(0, 0);
    style->FramePadding = ImVec2(0, 0);
    style->WindowPadding = ImVec2(0, 0);

    ImGui_ImplGlfw_InitForOpenGL(wind, true);
    ImGui_ImplOpenGL3_Init(OpenGL3_glsl_version);
}

void ImGuiHelper::ImGuiRenderDD()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}