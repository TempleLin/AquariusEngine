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
#include <headers/AQ_Scene.hpp>
#include <headers/AQ_CompSimpleBox2D.hpp>
#include <headers/AQ_CompBoxButton2D.hpp>
#include <headers/AQ_UniControls.h>
#include <headers/AQ_GlobalCtrl.hpp>
#include <headers/AQ_CompInput.hpp>

#include "headers/TwoDJavaGameIntegrate.hpp"
#include "headers/mainCharacterCallbacks.hpp"
#include "headers/firstButtonCallbacks.hpp"
#include "headers/glConfigCallbacks.h"


using namespace aquarius_engine;
using namespace stbi_image_wrap;

void glfwError(int id, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void create2DCubeVerts(unsigned int* vao, unsigned int* vbo, unsigned int* ebo);

AQ_OpenGL* aqOpenGL = new AQ_OpenGL();
GLFWwindow* currentWindow;
AQ_Shader* twoDShader;

int SCR_WIDTH{ 1280 }, SCR_HEIGHT{ 720 };

int main()
{
    ///*
    //* @Note: Shader can only be created after glfw init().
    //*/
    std::cout << "test" << std::endl;

    aqOpenGL->setOpenGL()
        .ver_Profile(3, 3, GLFW_OPENGL_CORE_PROFILE, &glfwError, false)
        .createWindow(SCR_WIDTH, SCR_HEIGHT, "TwoDJavaIntegrate", NULL, NULL, true)
        .setFrameBufferSizeCallback(aqOpenGL->getBoundWindow(), framebuffer_size_callback)
        .setCursorPosCallback(aqOpenGL->getBoundWindow(), MousePosCallback::mouse_callback)
        .setScrollCallback(aqOpenGL->getBoundWindow(), scroll_callback)
        .setCurrentThreadWindow(aqOpenGL->getBoundWindow())
        .initializeGLAD()
        .finishSettings();
    currentWindow = aqOpenGL->getBoundWindow();

    std::cout << "test" << std::endl;

    AQ_Scene* scene = new AQ_Scene(currentWindow);
    AQ_UniControls* uniControls = new AQ_UniControls(scene);
    AQ_GameObjectCtrl* gameObjectCtrl = uniControls->getGameObjectCtrl();
    AQ_GlobalCtrl* globalCtrl = uniControls->getGlobalCtrl();
    AQ_GlobalCtrl::InputSystemCtrl* inputSystemCtrl = globalCtrl->getInputSystemCtrl();
    AQ_GlobalCtrl::TimeCtrl* timeCtrl = globalCtrl->getTimeCtrl();

    stbi_image_wrap::setFlipVerticallyOnLoad(true);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    // -------- Create main character --------------
    AQ_GameObject* mainCharacter = gameObjectCtrl->createGameObject("MainCharacter");

    unsigned int mainCharVAO, mainCharVBO, mainCharEBO;
    create2DCubeVerts(&mainCharVAO, &mainCharVBO, &mainCharEBO);


    AQ_CompSimpleBox2D* mainChar2D = gameObjectCtrl->
        addComponent<AQ_CompSimpleBox2D>(mainCharacter, new AQ_CompSimpleBox2D(mainCharVAO, mainCharVBO, mainCharEBO, 6), "MainCharacter2D");
    mainChar2D->keepAspectRatio();
    // ---------------------------------------------
    mainCharacter->setCallbackFuncs(mainCharacter::start, mainCharacter::update, mainCharacter::stop);
    std::cout << "test" << std::endl;
    // -------- Create button ----------------------
    AQ_GameObject* firstBtn = gameObjectCtrl->createGameObject("FirstButton");
    AQ_CompBoxButton2D* firstBtn2D = gameObjectCtrl->addComponent<AQ_CompBoxButton2D>(firstBtn,
        new AQ_CompBoxButton2D(mainCharVAO, mainCharVBO, mainCharEBO, 6), "FirstButton2D");
    AQ_CompInput* firstBtnInput = gameObjectCtrl->addComponent<AQ_CompInput>(firstBtn, new AQ_CompInput(currentWindow, new unsigned int[1]{ GLFW_KEY_A },
        new unsigned int[1]{ GLFW_PRESS }, firstButton::processInputs, inputSystemCtrl), "FirstButtonInput");
    // ---------------------------------------------
    firstBtn->setCallbackFuncs(firstButton::start, firstButton::update, firstButton::stop);


    std::cout << "test" << std::endl;

    gameObjectCtrl->startGameObjects();
    // @The shader object gets back from gameObject created in start().
    AQ_Shader* mainCharacterShader = static_cast<AQ_Shader*>(mainCharacter->getOtherRefs()[0]);
    mainCharacterShader->use();


    while(!glfwWindowShouldClose(currentWindow)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(.0f, .0f, .0f, .0f);

        timeCtrl->updateTime();
        inputSystemCtrl->processInputs();
        gameObjectCtrl->updateGameObjects();

        glfwSwapBuffers(currentWindow);
    }

    glfwTerminate();
    delete twoDShader;
    gameObjectCtrl->stopGameObjects();
    gameObjectCtrl->deleteGameObject("MainCharacter");
    delete uniControls;
    delete scene;
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
