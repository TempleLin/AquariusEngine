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
#include "headers/glConfigCallbacks.hpp"
#include "headers/CustomButtonComp.hpp"
#include "headers/backgroundCallbacks.h"
#include "headers/PassingValues.hpp"


using namespace aquarius_engine;
using namespace stbi_image_wrap;

void glfwError(int id, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void create2DBackgroundVerts(unsigned int* vao, unsigned int* vbo, unsigned int* ebo);
void createChar_BtnVerts(unsigned int* vao, unsigned int* vbo, unsigned int* ebo);

AQ_OpenGL* aqOpenGL = new AQ_OpenGL();
GLFWwindow* currentWindow;
AQ_Shader* twoDShader;

int SCR_WIDTH{ 1280 }, SCR_HEIGHT{ 720 };

int main()
{
    ///*
    //* @Note: Shader can only be created after glfw init().
    //*/
    aqOpenGL->setOpenGL()
        .ver_Profile(3, 3, GLFW_OPENGL_CORE_PROFILE, &glfwError, false)
        .createWindow(SCR_WIDTH, SCR_HEIGHT, "TwoDJavaIntegrate", NULL, NULL, true)
        .setFrameBufferSizeCallback(aqOpenGL->getBoundWindow(), framebuffer_size_callback)
        .setScrollCallback(aqOpenGL->getBoundWindow(), scroll_callback)
        .setCurrentThreadWindow(aqOpenGL->getBoundWindow())
        .initializeGLAD()
        .finishSettings();
    currentWindow = aqOpenGL->getBoundWindow();

    stbi_image_wrap::setFlipVerticallyOnLoad(true);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    AQ_Scene* scene = new AQ_Scene(currentWindow);
    AQ_UniControls* uniControls = new AQ_UniControls(scene);
    AQ_GameObjectCtrl* gameObjectCtrl = uniControls->getGameObjectCtrl();
    AQ_GlobalCtrl* globalCtrl = uniControls->getGlobalCtrl();
    AQ_GlobalCtrl::InputSystemCtrl* inputSystemCtrl = globalCtrl->getInputSystemCtrl();
    AQ_GlobalCtrl::TimeCtrl* timeCtrl = globalCtrl->getTimeCtrl();


    shaders.push_back(AQ_Shader("assets/shaders/two_d_tex_vs.glsl", "assets/shaders/two_d_tex_fs.glsl"));

    // -------- Create background-------------------
    AQ_GameObject* backgroundObject = gameObjectCtrl->createGameObject("Background");
    unsigned int backgroundVAO{}, backgroundVBO{}, backgroundEBO{};
    create2DBackgroundVerts(&backgroundVAO, &backgroundVBO, &backgroundEBO);
    AQ_CompSimpleBox2D* background2D = gameObjectCtrl->
        addComponent<AQ_CompSimpleBox2D>(backgroundObject, new AQ_CompSimpleBox2D(backgroundVAO, backgroundVBO,
            backgroundEBO, 6), "Background2D");
    backgroundObject->setCallbackFuncs(background_callbacks::start, background_callbacks::update, background_callbacks::stop);
    // ---------------------------------------------

    // -------- Create main character --------------
    AQ_GameObject* mainCharacter = gameObjectCtrl->createGameObject("MainCharacter");

    unsigned int charAndBtnVAO, charAndBtnVBO, charAndBtnEBO;
    createChar_BtnVerts(&charAndBtnVAO, &charAndBtnVBO, &charAndBtnEBO);

    AQ_CompSimpleBox2D* mainChar2D = gameObjectCtrl->
        addComponent<AQ_CompSimpleBox2D>(mainCharacter, new AQ_CompSimpleBox2D(charAndBtnVAO, charAndBtnVBO, charAndBtnEBO, 6), "MainCharacter2D");
    mainChar2D->keepAspectRatio();
    mainCharacter->setCallbackFuncs(mainCharacter::start, mainCharacter::update, mainCharacter::stop);
    // ---------------------------------------------

    // -------- Create button ----------------------
    AQ_GameObject* firstBtn = gameObjectCtrl->createGameObject("FirstButton");
    CustomButtonComp* firstBtn2D = gameObjectCtrl->addComponent<CustomButtonComp>(firstBtn,
        new CustomButtonComp(charAndBtnVAO, charAndBtnVBO, charAndBtnEBO, 6), "FirstButton2D");
    AQ_CompInput* firstBtnInput = gameObjectCtrl->addComponent<AQ_CompInput>(firstBtn, new AQ_CompInput(currentWindow, new unsigned int[1]{ GLFW_KEY_A },
        new unsigned int[1]{ GLFW_PRESS }, firstButton::processInputs, inputSystemCtrl), "FirstButtonInput");
    firstBtn->setCallbackFuncs(firstButton::start, firstButton::update, firstButton::stop);
    // ---------------------------------------------


    gameObjectCtrl->startGameObjects();
    // @The shader object gets back from gameObject created in start().


    while(!glfwWindowShouldClose(currentWindow)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.f, 1.f, 1.f, 1.f);

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

    unsigned int buffersToDel[4]{ charAndBtnVBO, charAndBtnEBO, backgroundVBO, backgroundEBO };
    unsigned int vertexArraysToDel[2]{ charAndBtnVAO, backgroundVAO };

    glDeleteVertexArrays(1, vertexArraysToDel);
    glDeleteBuffers(4, buffersToDel);
}

void create2DBackgroundVerts(unsigned int* vao, unsigned int* vbo, unsigned int* ebo) {
    float vertices[] = {
        // positions          // colors           // texture coords
         1.f,  1.f, .0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
         1.f, -1.f, .0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
        -1.f, -1.f, .0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -1.f,  1.f, .0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left 
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

void createChar_BtnVerts(unsigned int* vao, unsigned int* vbo, unsigned int* ebo) {
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, -1.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, -1.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, -1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, -1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left 
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
