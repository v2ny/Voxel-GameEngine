#include <GUI.h>
#include <windows.h>
#include <iostream>

void GUI_CLASS::GUI_CLASS_REGISTERES(GLFWwindow* wind)
{
    if(wind != nullptr)
    {
        this->win = wind;
    }
    else
    {
        MessageBox(nullptr, "GLFW Window is null pointer! \nFrom: GUI_CLASS_REGISTERS(GLFWwindow* wind)\nWanted:                    ^^^^", "Error", MB_OK | MB_ICONERROR);
        return;
    }
}

void GUI_CLASS::Place(Shader shr)
{
    ImGui::NewFrame();
	{
        if(ImGui::Begin("Spot Lighting"))
        {
            ImGui::Text("SHR Spot Ranges :-");

            ImGui::Text("Inner Cone :");
            ImGui::InputFloat("Inner Cone Size", &appGui_ICS);

            ImGui::Text("Outter Cone :");
            ImGui::InputFloat("Outter Cone Size", &appGui_OCS);
        }

        ImGui::End();
    }
}