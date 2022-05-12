#include <Camera.h>

Camera::Camera(int viewportWidth, int viewportHeight, glm::vec3 Position, GLFWwindow* window)
{
    this->vpWidth = viewportWidth;
    this->vpHeight = viewportHeight;
    this->Position = Position;
    this->wind = window;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    float windowSavedW = vpWidth;
    float windowSavedH = vpHeight;

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    // Just to make sure that it doesnt make the aspect-ratio 0
    if(windowSavedW < 200)
    {
        projection = glm::perspective(glm::radians(FOVdeg), (float)(1024 / 600), nearPlane, farPlane);
    }
    else if(windowSavedW > 200)
    {
        projection = glm::perspective(glm::radians(FOVdeg), (windowSavedW / windowSavedH), nearPlane, farPlane);
    }
    
    glfwGetFramebufferSize(wind, &vpWidth, &vpHeight);
    
    // To get the window size
    {
        int winNewWidth, winNewHeight;
        glfwGetWindowSize(wind, &winNewWidth, &winNewHeight);
        windowSavedW = winNewWidth;
        windowSavedH = winNewHeight;
    }

    cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(GLFWwindow* window)
{
    float cameraUpClip = 89.0f;
    float cameraBottomClip = -84.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Position += Speed * Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Position += Speed * -glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Position += Speed * -Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Position += Speed * glm::normalize(glm::cross(Orientation, Up));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        Position += Speed * Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        Position += Speed * -Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        Speed = 0.023f;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        Speed = 0.01f;
    }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if(firstClick)
        {
            glfwSetCursorPos(window, (vpWidth / 2), (vpHeight / 2));
            firstClick = false;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = Sensitivity * (float)(mouseY - (vpHeight / 2)) / vpHeight;
        float rotY = Sensitivity * (float)(mouseX - (vpWidth / 2)) / vpWidth;

        glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		// Rotates the Orientation left and right
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

        glfwSetCursorPos(window, (vpWidth / 2), (vpHeight / 2));
    }
    else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}