#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ImGuiHelper.h>
#include <ShaderClass.h>

class GUI_CLASS
{
    public:
        float appGui_OCS = 0.90f;
        float appGui_ICS = 0.95f;
        
        void GUI_CLASS_REGISTERES(GLFWwindow* wind);
        void Place(Shader shr);

    protected:
        GLFWwindow* win;
};
