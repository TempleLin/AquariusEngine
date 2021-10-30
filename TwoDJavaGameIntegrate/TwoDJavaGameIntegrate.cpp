#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <headers/AQ_GLIntegrate.hpp>
#include <headers/AQ_Shader.hpp>
#include <headers/stbi_image_wrapper.hpp>
#include <headers/AQ_GameObjectCtrl.hpp>
#include <headers/AQ_GameObject.hpp>
#include <headers/AQ_Database.hpp>
#include <headers/AQ_CompSimple2D.hpp>
#include <headers/AQ_GlobalCtrl.hpp>

#include "mainCharacterCallbacks.hpp"

using namespace aquarius_engine;
using namespace stbi_image_wrap;

void glfwError(int id, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mainCharacterPreDrawCallback(unsigned int shaderID, unsigned int* uniforms);

void createCharacterVertices(unsigned int* vao, unsigned int* vbo, unsigned int* ebo);

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


    ///*
    //* @Note: Shader can only be created after glfw init().
    //*/
    twoDShader = new AQ_Shader("assets/shaders/two_d_tex_vs.glsl", "assets/shaders/two_d_tex_fs.glsl");

    AQ_Database::GameObjects* gameObjectsDatabase = new AQ_Database::GameObjects();
    AQ_Database::Components* componentsDatabase = new AQ_Database::Components();
    AQ_GameObjectCtrl* gameObjectCtrl = new AQ_GameObjectCtrl(componentsDatabase, gameObjectsDatabase);
    AQ_GlobalCtrl::TimeCtrl* timeCtrl = new AQ_GlobalCtrl::TimeCtrl;

    // -------- Create main character --------------
    AQ_GameObject* mainCharacter = gameObjectCtrl->createGameObject("MainCharacter");

    unsigned int mainCharVAO, mainCharVBO, mainCharEBO;
    createCharacterVertices(&mainCharVAO, &mainCharVBO, &mainCharEBO);

    AQ_CompSimple2D* mainChar2D = gameObjectCtrl->
        addComponent<AQ_CompSimple2D>(mainCharacter, new AQ_CompSimple2D(mainCharVAO, mainCharVBO, mainCharEBO, 6), "MainCharacter2D");
    // ---------------------------------------------

    mainCharacter->setStartCallback(mainCharacter::start);
    mainCharacter->setUpdateCallback(mainCharacter::update);

    stbi_image_wrap::setFlipVerticallyOnLoad(true);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    gameObjectCtrl->startGameObjects();


    while(!glfwWindowShouldClose(currentWindow)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(.0f, .0f, .0f, .0f);

        timeCtrl->updateTime();

        gameObjectCtrl->updateGameObjects();

        glfwSwapBuffers(currentWindow);
    }

    glfwTerminate();
    delete twoDShader;
    gameObjectCtrl->stopGameObjects();
    gameObjectCtrl->deleteGameObject("MainCharacter");
    delete gameObjectCtrl;
    delete gameObjectsDatabase;
    delete componentsDatabase;
    delete timeCtrl;
}

void createCharacterVertices(unsigned int* vao, unsigned int* vbo, unsigned int* ebo) {
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
    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
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
}

void mainCharacterPreDrawCallback(unsigned int shaderID, unsigned int* uniforms) {
    glUseProgram(shaderID);
    glUniform1f(uniforms[0], (float)SCR_WIDTH);
    glUniform1f(uniforms[1], (float)SCR_HEIGHT);
    glUniform1i(uniforms[2], GLFW_TRUE);
    glm::mat4 offsetMatrix(1.f);
    offsetMatrix = glm::translate(offsetMatrix, glm::vec3(-.5f, 0.f, 0.f));
    glUniformMatrix4fv(uniforms[3], 1, false, &offsetMatrix[0][0]);
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

void glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}