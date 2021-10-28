#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <headers/AQ_GLIntegrate.hpp>

using namespace aquarius_engine;

static void glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}

AQ_OpenGL* aqOpenGL = new AQ_OpenGL();
GLFWwindow* currentWindow;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int SCR_WIDTH{ 1280 }, SCR_HEIGHT{ 720 };

int main()
{
    aqOpenGL->setOpenGL()
        .ver_Profile(3, 3, GLFW_OPENGL_CORE_PROFILE, &glfwError)
        .createWindow(SCR_WIDTH, SCR_HEIGHT, "TwoDJavaIntegrate", NULL, NULL, true)
        .setFrameBufferSizeCallback(aqOpenGL->getBoundWindow(), framebuffer_size_callback)
        .setCursorPosCallback(aqOpenGL->getBoundWindow(), mouse_callback)
        .setScrollCallback(aqOpenGL->getBoundWindow(), scroll_callback)
        .setCurrentThreadWindow(aqOpenGL->getBoundWindow())
        .initializeGLAD()
        .finishSettings();
    currentWindow = aqOpenGL->getBoundWindow();

    while(!glfwWindowShouldClose(currentWindow)) {
        glfwPollEvents();
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(currentWindow);
    }

    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    //if (firstMouse) {
    //    lastX = xpos;
    //    lastY = ypos;
    //    firstMouse = false;
    //}

    //float xoffset = xpos - lastX;
    //float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    //lastX = xpos;
    //lastY = ypos;

    //camera->processMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    //camera->processMouseScroll(yoffset);
}