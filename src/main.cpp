#include <Mesh.h>

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

// Vertices coordinates
Vertex vertices[] =
{ //               COORDINATES           /            COLORS          /           TexCoord         /       NORMALS         //
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3
};

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
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

    Texture textures[]
    {
        Texture("binaries/pkgs/imgs/materials/Tiles/tdiuse.img.obj", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("binaries/pkgs/imgs/materials/Tiles/tspec.img.obj", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };

    // Send a test MessageBox with our new function
    // box_l.Log("A basic message", "message", nullptr, box_l.info);

    Shader shaderProgram("binaries/incl_shaders/vrtx.s.obj", "binaries/incl_shaders/frgmnt.s.obj");
    std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector <GLuint> ind(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	// Create floor mesh
	Mesh floor(verts, ind, tex);

    // Shader for light cube
	Shader lightShader("binaries/incl_shaders/lght.vrtx.s.obj", "binaries/incl_shaders/lght.frgmnt.s.obj");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	// Crate light mesh
	Mesh light(lightVerts, lightInd, tex);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        
        // Draws our meshs
        floor.Draw(shaderProgram, player0);
        light.Draw(lightShader, player0);

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
	lightShader.Delete();
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