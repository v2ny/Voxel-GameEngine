#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <floatsToRGB.h>
#include <BoxLogger.h>
#include <cmath>

#include <Texture.h>
#include <ShaderClass.h>
#include <Organizing/VAO/VAO.h>
#include <Organizing/VBO/VBO.h>
#include <Organizing/EBO/EBO.h>
#include <Camera.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <CustomMessageBox.h>
#include <GUI.h>

// [-----------------Default opts-----------------]

// Dimensions
static int wWidth = 1024;
static int wHeight = 600;

// Window title
const char* wTitle = "Voxel-GameEngine";

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS        /    TexCoord    /       NORMALS     //
	-1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 0.0f,		0.0f, 1.0f, 0.0f,
	-1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		0.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 1.0f,		0.0f, 1.0f, 0.0f,
	 1.0f, 0.0f,  1.0f,		0.0f, 0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

int main()
{
    // Define floatsToRGB
    rgbConverter rgbConv;
    // Define BoxLogger
    BoxLogger box_l;
    // Define ImGuiHelper
    ImGuiHelper igh;
    // Define GUI
    GUI_CLASS AppGui;

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

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO to VAO
	VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttribute(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttribute(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

    // Shader for light cube
	Shader lightShader("binaries/incl_shaders/lght.vrtx.s.obj", "binaries/incl_shaders/lght.frgmnt.s.obj");
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttribute(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Texture
    Texture tex1("binaries/pkgs/imgs/materials/Tiles/tdiuse.img.obj", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    tex1.texUnit(shaderProgram, "tex0", 0);
    Texture tex2("binaries/pkgs/imgs/materials/Tiles/tspec.img.obj", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    tex2.texUnit(shaderProgram, "tex1", 0);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

    // Camera object
    Camera player0(wWidth, wHeight, glm::vec3(0.0f, 0.0f, 2.0f), window);

    // Sets the default settings for imgui and use a custom font
    igh.ImGuiDefaultSettings(window, "binaries/pkgs/fonts/lgeorgecfeb.fnt.obj", "#version 330 core");

    // Registers the glfw window to the AppGui
    AppGui.GUI_CLASS_REGISTERES(window);
    
    // Shows our window
    glfwShowWindow(window);

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Perspective fov
        static float fov = 75.0f;

        // Distance View
        static float nearDistanceView = 0.01f;
        static float farDistanceView = 500.0f;

        // Aspect Ratio
        static float svd_width = wWidth;
        static float svd_height = wHeight;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        AppGui.Place(shaderProgram);
        ImGui::Render();

        player0.Inputs(window);
        player0.updateMatrix(fov, nearDistanceView, farDistanceView);

        // It explains it self
        shaderProgram.Activate();
        
        GLuint ics = glGetUniformLocation(shaderProgram.ID, "innerConeSize");
        GLuint ocs = glGetUniformLocation(shaderProgram.ID, "outterConeSize");

        glUniform1f(ics, AppGui.appGui_ICS);
        glUniform1f(ocs, AppGui.appGui_OCS);

        glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), player0.Position.x, player0.Position.y, player0.Position.z);
		// Export the camMatrix to the Vertex Shader of the pyramid
		player0.Matrix(shaderProgram, "camMatrix");
        // Bind the textures
        tex1.Bind();
        tex2.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        // Activating Light Shader
        lightShader.Activate();
		// Export the camMatrix to the Vertex Shader of the light cube
		player0.Matrix(lightShader, "camMatrix");
		// Bind the VAO so OpenGL knows to use it
		lightVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		// glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

        // Bind the Texture to display it?

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
        igh.ImGuiRenderDD();

        // Important to get our window working properly!
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
    tex1.Delete();
	shaderProgram.Delete();
    lightVAO.Delete();
	lightVBO.Delete();
	lightEBO.Delete();
	lightShader.Delete();
    // Delete's ImGui Rendering Stuff
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // Delete window before ending the program
	glfwDestroyWindow(window);
    // To exit the window when it leaves the while loop (It leaves the while loop if there's an close/crash interupt)
    glfwTerminate();
    return 0;
}