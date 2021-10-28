#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <headers/AQ_GLIntegrate.hpp>
#include <headers/AQ_Shader.hpp>
#include <headers/stbi_image_wrapper.hpp>

using namespace aquarius_engine;
using namespace stbi_image_wrap;

static void glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int SCR_WIDTH{ 1280 }, SCR_HEIGHT{ 720 };

AQ_OpenGL* aqOpenGL = new AQ_OpenGL();
GLFWwindow* currentWindow;
AQ_Shader* twoDShader;

int main()
{

    aqOpenGL->setOpenGL()
        .ver_Profile(3, 3, GLFW_OPENGL_CORE_PROFILE, &glfwError, false)
        .createWindow(SCR_WIDTH, SCR_HEIGHT, "TwoDJavaIntegrate", NULL, NULL, true)
        .setFrameBufferSizeCallback(aqOpenGL->getBoundWindow(), framebuffer_size_callback)
        .setCursorPosCallback(aqOpenGL->getBoundWindow(), mouse_callback)
        .setScrollCallback(aqOpenGL->getBoundWindow(), scroll_callback)
        .setCurrentThreadWindow(aqOpenGL->getBoundWindow())
        .initializeGLAD()
        .finishSettings();
    currentWindow = aqOpenGL->getBoundWindow();

    /*
    * @Note: These need to be set to have transparent background image.
    */
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    unsigned int VAO, VBO, EBO;

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


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

    unsigned char* data = loadImage("assets/cleanCharacter.png", width, height, nrChannels);
    if (data) {

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture1." << std::endl;
    }
    // @Free the image memory.
    freeImage(data);

    /*
    * @Note: Shader can only be created after glfw init().
    */
    twoDShader = new AQ_Shader("assets/shaders/two_d_tex_vs.glsl", "assets/shaders/two_d_tex_fs.glsl");
    twoDShader->use();

    unsigned int uniWinWidth = glGetUniformLocation(twoDShader->ID, "windowWidth");
    unsigned int uniWinHeight = glGetUniformLocation(twoDShader->ID, "windowHeight");
    unsigned int uniKeepAspectRatio = glGetUniformLocation(twoDShader->ID, "keepAspectRatio");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);


    while(!glfwWindowShouldClose(currentWindow)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(.0f, .0f, .0f, .0f);

        glBindTexture(GL_TEXTURE_2D, texture1);
        twoDShader->use();
        glUniform1i(uniKeepAspectRatio, GLFW_TRUE);
        glUniform1f(uniWinWidth, (float)SCR_WIDTH);
        glUniform1f(uniWinHeight, (float)SCR_HEIGHT);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(currentWindow);
    }

    glfwTerminate();
    delete twoDShader;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
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