#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <headers/AQ_GLIntegrate.hpp>
#include <headers/stbi_image_wrapper.hpp>

using namespace aquarius_engine;
using namespace stbi_image_wrap;

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

    unsigned int texture1;
    glGenTextures(1, &texture1);

    /*
    * @If there's only one texture unit, there's no need to sett the active texture unit bc default texture unit is already 0.
    * And it will automatically pass into the fragment shader's uniform sampler2D variable.
    */
    glBindTexture(GL_TEXTURE_2D, texture1); // @Bind it so any subsequent texture commands will configure the currently bound texture.

    // @Set the texture wrapping/filtering options (on the currently bound texture object).
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels/*Number of color channels.*/;
    setFlipVerticallyOnLoad(true); // @Tell stb_image.h to flip loaded texture's on the y-axis.

    unsigned char* data = loadImage("assets/cleanCharacter.jpg", width, height, nrChannels);
    if (data) {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture1." << std::endl;
    }
    // @Free the image memory.
    freeImage(data);

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