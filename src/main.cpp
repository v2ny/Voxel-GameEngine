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

int wWidth = 1024;
int wHeight = 600;
const char* wTitle = "Voxel-GameEngine";

// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f, // Lower left corner
	-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f, // Upper right corner
	 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f  // Lower right corner
};

// Indices for vertices order
GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2 // Lower triangle
};

int main()
{
    // Define floatsToRGB
    rgbConverter rgbConv;
    // Define BoxLogger
    BoxLogger box_l;

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

    // Let's implement our opengl/window viewport
    glViewport(0, 0, wWidth, wHeight);

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

    while(!glfwWindowShouldClose(window))
    {
        // To hide the console for windows
        HWND hWnd = GetConsoleWindow();
        ShowWindow( hWnd, SW_HIDE );

        // Let's clear our color buffer bit to get our background color appear!
        glClear(GL_COLOR_BUFFER_BIT);

        // It explains it self
        shaderProgram.Activate();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        projection = glm::perspective(glm::radians(85.0f), (float)(wWidth / wHeight), 0.01f, 100.0f);

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
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

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
	glfwDestroyWindow(window);
    // To exit the window when it leaves the while loop (It leaves the while loop if there's an close/crash interupt)
    glfwTerminate();
    return 0;
}