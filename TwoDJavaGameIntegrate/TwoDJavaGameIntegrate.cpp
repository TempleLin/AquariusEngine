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

#include "headers/TwoDJavaGameIntegrate.hpp"
#include "headers/mainCharacterCallbacks.hpp"
#include "headers/firstButtonCallbacks.hpp"

using namespace aquarius_engine;
using namespace stbi_image_wrap;

void glfwError(int id, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mainCharacterPreDrawCallback(unsigned int shaderID, unsigned int* uniforms);
void create2DCubeVerts(unsigned int* vao, unsigned int* vbo, unsigned int* ebo);

AQ_OpenGL* aqOpenGL = new AQ_OpenGL();
GLFWwindow* currentWindow;
AQ_Shader* twoDShader;

int SCR_WIDTH{ 1280 }, SCR_HEIGHT{ 720 };

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
    AQ_Database::GameObjects* gameObjectsDatabase = new AQ_Database::GameObjects();
    AQ_Database::Components* componentsDatabase = new AQ_Database::Components();
    AQ_GameObjectCtrl* gameObjectCtrl = new AQ_GameObjectCtrl(componentsDatabase, gameObjectsDatabase);
    AQ_GlobalCtrl::TimeCtrl* timeCtrl = new AQ_GlobalCtrl::TimeCtrl;

    stbi_image_wrap::setFlipVerticallyOnLoad(true);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    // -------- Create main character --------------
    AQ_GameObject* mainCharacter = gameObjectCtrl->createGameObject("MainCharacter");

    unsigned int mainCharVAO, mainCharVBO, mainCharEBO;
    create2DCubeVerts(&mainCharVAO, &mainCharVBO, &mainCharEBO);

    AQ_CompSimple2D* mainChar2D = gameObjectCtrl->
        addComponent<AQ_CompSimple2D>(mainCharacter, new AQ_CompSimple2D(mainCharVAO, mainCharVBO, mainCharEBO, 6), "MainCharacter2D");
    // ---------------------------------------------
    mainCharacter->setCallbackFuncs(mainCharacter::start, mainCharacter::update, mainCharacter::stop);

    // -------- Create button ----------------------
    AQ_GameObject* firstBtn = gameObjectCtrl->createGameObject("FirstButton");
    AQ_CompSimple2D* firstBtn2D = gameObjectCtrl->addComponent<AQ_CompSimple2D>(firstBtn,
        new AQ_CompSimple2D(mainCharVAO, mainCharVBO, mainCharEBO, 6), "FirstButton2");
    // ---------------------------------------------
    firstBtn->setCallbackFuncs(firstButton::start, firstButton::update, firstButton::stop);


    gameObjectCtrl->startGameObjects();
    // @The shader object gets back from gameObject created in start().
    AQ_Shader* mainCharacterShader = static_cast<AQ_Shader*>(mainCharacter->getOtherRefs()[0]);
    mainCharacterShader->use();


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
    glDeleteVertexArrays(1, &mainCharVAO);
    glDeleteBuffers(1, &mainCharVBO);
    glDeleteBuffers(1, &mainCharEBO);
}

void create2DCubeVerts(unsigned int* vao, unsigned int* vbo, unsigned int* ebo) {
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
