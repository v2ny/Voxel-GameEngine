#include <Model.h>

#include <floatsToRGB.h>
#include <BoxLogger.h>

#include <CustomMessageBox.h>
#include <GUI.h>

// [-----------------Default opts-----------------]

// Dimensions
static int wWidth = 1024;
static int wHeight = 600;

// Window title
const char* wTitle = "Voxel-GameEngine";

int main()
{
    // Define floatsToRGB
    rgbConverter rgbConv;
    // Define BoxLogger
    BoxLogger box_l;
    // Define ImGuiHelper
    ImGuiHelper igh;
    // Define GUI
    // GUI_CLASS AppGui;

    // At the first initialize glfw
    glfwInit();

    // Specific GlfwWindowHints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Let's create our glfwWindow
    GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, wTitle, NULL, NULL);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window!\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Now let's check for glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD!\n";
        return -1;
    }  
    gladLoadGL();

    // Hides the window 
    glfwHideWindow(window);

    // Send a test MessageBox with our new function
    // box_l.Log("A basic message", "message", nullptr, box_l.info);

    Shader shaderProgram("binaries/incl_shaders/vrtx.s.obj", "binaries/incl_shaders/frgmnt.s.obj");
    // Shader outliningProgram("binaries/incl_shaders/outline.vrtx.s.obj", "binaries/incl_shaders/outline.frgmnt.s.obj");

    // Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

    // Camera object
    Camera player0(wWidth, wHeight, glm::vec3(0.0f, 0.0f, 2.0f), window);

    // Sets the default settings for imgui and use a custom font
    // igh.ImGuiDefaultSettings(window, "binaries/pkgs/fonts/lgeorgecfeb.fnt.obj", "#version 330 core");

    // Registers the glfw window to the AppGui
    // AppGui.GUI_CLASS_REGISTERES(window);

    Model model1("binaries/pkgs/mdls/cube/scene.gltf");
    Model model2("binaries/pkgs/mdls/sword/scene.gltf");

    // Shows our window
    glfwShowWindow(window);

    // Turns on VSync
    glfwSwapInterval(1);

    // Game Logic
    while(!glfwWindowShouldClose(window))
    {
        // A boolean to know when to show the Console and hide it
        static bool CONSOLE_SHOW = false;
        
        if (CONSOLE_SHOW == false)
        {
            // To hide the console for windows
            HWND hWnd = GetConsoleWindow();
            ShowWindow( hWnd, SW_HIDE );
        }
        if (CONSOLE_SHOW == true)
        {
            // To show the console for windows
            HWND hWnd = GetConsoleWindow();
            ShowWindow( hWnd, SW_SHOW );
        }
        
        // Let's select a background color for our window
        glClearColor(rgbConv.convert(60.0f), rgbConv.convert(90.0f), rgbConv.convert(170.0f), 1.0f);
        // Let's clear our color buffer bit to get our background color appear!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // Perspective fov
        static float fov = 75.0f;

        // Distance View
        static float nearDistanceView = 0.01f;
        static float farDistanceView = 500.0f;

        // Aspect Ratio
        static float svd_width = wWidth;
        static float svd_height = wHeight;

        // ImGui_ImplOpenGL3_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        // AppGui.Place(shaderProgram);
        // ImGui::Render();

        player0.Inputs(window);
        player0.updateMatrix(fov, nearDistanceView, farDistanceView);

        // GLuint ics = glGetUniformLocation(shaderProgram.ID, "innerConeSize");
        // GLuint ocs = glGetUniformLocation(shaderProgram.ID, "outterConeSize");

        // glUniform1f(ics, AppGui.appGui_ICS);
        // glUniform1f(ocs, AppGui.appGui_OCS);

        // Draw a model
		model1.Draw(shaderProgram, player0);
		model2.Draw(shaderProgram, player0);

        // Let's implement our opengl/window viewport
        {
            int winNewWidth;
            int winNewHeight;
            glfwGetWindowSize(window, &winNewWidth, &winNewHeight);

            svd_width = winNewWidth;
            svd_height = winNewHeight;

            glViewport(0, 0, winNewWidth, winNewHeight);
        }

        // ImGui Render Draw Data
        // igh.ImGuiRenderDD();

        // Important to get our window working properly!
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete all the objects we've created
	shaderProgram.Delete();
    // Delete's ImGui Rendering Stuff
    // ImGui_ImplOpenGL3_Shutdown();
    // ImGui_ImplGlfw_Shutdown();
    // ImGui::DestroyContext();
    // Delete window before ending the program
	glfwDestroyWindow(window);
    // To exit the window when it leaves the while loop (It leaves the while loop if there's an close/crash interupt)
    glfwTerminate();
    return 0;
}