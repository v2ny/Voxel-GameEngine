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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ImGuiHelper.h>

int wWidth = 1024;
int wHeight = 600;
const char* wTitle = "Voxel-GameEngine";

// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main()
{
    // Define floatsToRGB
    rgbConverter rgbConv;
    // Define BoxLogger
    BoxLogger box_l;
    // Define ImGuiHelper
    ImGuiHelper igh;

    // At the first initialize glfw
    glfwInit();

    // Specific GlfwWindowHints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    // Let's select a background color for our window
    glClearColor(rgbConv.convert(50.0f), rgbConv.convert(50.0f), rgbConv.convert(50.0f), 1.0f);

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
	VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttribute(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Texture
    Texture tex1("binaries/pkgs/imgs/ghpng.img.obj", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    tex1.texUnit(shaderProgram, "tex0", 0);

    // Variables that help the rotation of the pyramid
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

    // Sets the default settings for imgui and use a custom font
    igh.ImGuiDefaultSettings(window, "binaries/pkgs/fonts/lgeorgecfeb.fnt.obj", "#version 330 core");

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

        // Let's clear our color buffer bit to get our background color appear!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Perspective fov
        static float fov = 45.0f;

        // Distance View
        static float nearDistanceView = 0.01f;
        static float farDistanceView = 100.0f;

        // Aspect Ratio
        static float svd_width = wWidth;
        static float svd_height = wHeight;

        // Pyramid position
        static float posX = 0.0f;
        static float posY = 1.0f;
        static float posZ = 0.0f;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
		{
            ImGui::SetNextWindowSize(ImVec2(260, (svd_height)));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSizeConstraints(ImVec2(260, (svd_height)), ImVec2(260, (svd_height)));

            bool is_open = true;
            bool is_open2 = true;

            static bool cameraSelected = false;
            static bool pyramidSelected = false;

            if (ImGui::Begin("game_obj_list", &is_open, ImGuiWindowFlags_NoTitleBar))
            {
                std::string objListTitle = "Game Objects List";
                auto windowWidth = ImGui::GetWindowSize().x;
                auto textWidth   = ImGui::CalcTextSize(objListTitle.c_str()).x;

                ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
                ImGui::Text(objListTitle.c_str());
                if (ImGui::Button("Camera", ImVec2(ImGui::GetWindowSize().x, 20)))
                {
                    cameraSelected = true;
                    pyramidSelected = false;
                }
                if (ImGui::Button("Pyramid", ImVec2(ImGui::GetWindowSize().x, 20)))
                {
                    pyramidSelected = true;
                    cameraSelected = false;
                }
            }
            
            ImGui::End();

            ImGui::SetNextWindowSize(ImVec2(260, (svd_height / 1.5)));
            ImGui::SetNextWindowPos(ImVec2(((svd_width) - 260), 0));
            ImGui::SetNextWindowSizeConstraints(ImVec2(260, (svd_height / 1.5)), ImVec2(260, (svd_height / 1.5)));

            if (ImGui::Begin("obj_properties", &is_open2, ImGuiWindowFlags_NoTitleBar))
            {
                std::string objListTitle = "Object Properties";
                static const char* status = "\nNo game object selected!";

                auto windowWidth = ImGui::GetWindowSize().x;
                auto textWidth   = ImGui::CalcTextSize(objListTitle.c_str()).x;

                ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
                ImGui::Text(objListTitle.c_str());
                ImGui::Text(status);
                if(cameraSelected == true)
                {
                    status = "Game Object: Camera";
                    ImGui::Text("Camera Position :-");
                    ImGui::InputFloat("X", &posX, -360.0f, 360.0f, "%.1f", 0);
                    ImGui::InputFloat("Y", &posY, -360.0f, 360.0f, "%.1f", 0);
                    ImGui::InputFloat("Z", &posZ, -360.0f, 360.0f, "%.1f", 0);
                    ImGui::Text("Camera Options :-");
                    ImGui::SliderFloat("FOV", &fov, 30.0f, 130.0f, "%.1f", 1.0f);
                    ImGui::SliderFloat("Near Clip", &nearDistanceView, 0.01f, 10.0f, "%.1f", 1.0f);
                    ImGui::SliderFloat("Far Clip", &farDistanceView, 5.0f, 1500.0f, "%.1f", 1.0f);
                }
                else if(pyramidSelected == true)
                {
                    status = "Game Object: Pyramid";
                    ImGui::Text("Pyramid Position :-");
                    ImGui::SliderFloat("X", &posX, -360.0f, 360.0f, "%.1f", 1.0f);
                    ImGui::SliderFloat("Y", &posY, -360.0f, 360.0f, "%.1f", 1.0f);
                    ImGui::SliderFloat("Z", &posZ, -360.0f, 360.0f, "%.1f", 1.0f);
                }
                else
                {
                    status = "\nNo game object selected!";
                }
            }

            ImGui::End();

            ImGui::SetNextWindowSize(ImVec2(svd_width - (260 * 2), svd_height / 0.5));
            ImGui::SetNextWindowPos(ImVec2(svd_width - (260 * 2), svd_height / 0.5));
            ImGui::SetNextWindowSizeConstraints(ImVec2(svd_width - (260 * 2), svd_height / 0.5), ImVec2(svd_width - (260 * 2), svd_height / 0.5));

            if (ImGui::Begin("console_output", &is_open2, ImGuiWindowFlags_NoTitleBar))
            {
                std::string objListTitle = "Console Output";
                auto windowWidth = ImGui::GetWindowSize().x;
                auto textWidth   = ImGui::CalcTextSize(objListTitle.c_str()).x;

                ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
                ImGui::Text(objListTitle.c_str());
            }

            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        // It explains it self
        shaderProgram.Activate();

        // Simple timer
        double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(posX, posY, posZ));
        if(svd_width < 200)
        {
            projection = glm::perspective(glm::radians(fov), (float)(1024 / 600), nearDistanceView, farDistanceView);
        }
        else if(svd_width > 200)
        {
            projection = glm::perspective(glm::radians(fov), (float)(svd_width / svd_height), nearDistanceView, farDistanceView);
        }

        int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projectionLoc = glGetUniformLocation(shaderProgram.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glUniform1f(uniID, 0.5f);
        tex1.Bind();

		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        // Let's implement our opengl/window viewport
        {
            int winNewWidth;
            int winNewHeight;
            glfwGetWindowSize(window, &winNewWidth, &winNewHeight);

            svd_width = winNewWidth;
            svd_height = winNewHeight;

            glViewport(260, 0, winNewWidth - (260 * 2), winNewHeight - (winNewHeight / 0.5));
        }

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
    // Delete window before ending the program
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
	glfwDestroyWindow(window);
    // To exit the window when it leaves the while loop (It leaves the while loop if there's an close/crash interupt)
    glfwTerminate();
    return 0;
}