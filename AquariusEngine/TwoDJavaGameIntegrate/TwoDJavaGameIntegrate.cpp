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

#include "dear_imgui/imgui.h"
#include "dear_imgui/imgui_impl_glfw.h"
#include "dear_imgui/imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include "headers/TwoDJavaGameIntegrate.hpp"
#include "headers/mainCharacterCallbacks.hpp"
#include "headers/shortcutButtonCallbacks.hpp"
#include "headers/glConfigCallbacks.hpp"
#include "headers/CustomButtonComp.hpp"
#include "headers/backgroundCallbacks.h"
#include "headers/PassingValues.hpp"
#include "headers/backpackButtonsCallbacks.h"
#include "headers/shopCallbacks.h"


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
    AQ_GlobalCtrl::AudioSystemCtrl* audioSystemCtrl = globalCtrl->getAudioSystemCtrl();


    const char* glsl_version = "#version 330";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    //ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplGlfw_InitForOpenGL(currentWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


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
    AQ_GameObject* shortcutBtns = gameObjectCtrl->createGameObject("ShortcutButtons");
    CustomButtonComp* mainhallBtn = gameObjectCtrl->addComponent<CustomButtonComp>(shortcutBtns,
        new CustomButtonComp(charAndBtnVAO, charAndBtnVBO, charAndBtnEBO, 6), "MainHallButton2D");
    AQ_CompInput* shortcutInput = gameObjectCtrl->addComponent<AQ_CompInput>(shortcutBtns, new AQ_CompInput(currentWindow, new unsigned int[1]{ GLFW_KEY_A },
        new unsigned int[1]{ GLFW_PRESS }, shortcutButton::processInputs, inputSystemCtrl), "ShortcutButtonInput");
    shortcutBtns->setCallbackFuncs(shortcutButton::start, shortcutButton::update, shortcutButton::stop);
    // ---------------------------------------------

    // -------- Backpack button ---------------------
    AQ_GameObject* backpackBtns = gameObjectCtrl->createGameObject("BackpackButtons");

    CustomButtonComp* backPackClotheBtn = gameObjectCtrl->addComponent<CustomButtonComp>(backpackBtns,
        new CustomButtonComp(charAndBtnVAO, charAndBtnVBO, charAndBtnEBO, 6), "BackpackClotheBtn2D");

    CustomButtonComp* backPackWeaponsBtn = gameObjectCtrl->addComponent<CustomButtonComp>(backpackBtns,
        new CustomButtonComp(charAndBtnVAO, charAndBtnVBO, charAndBtnEBO, 6), "BackpackWeaponsBtn2D");

    AQ_CompInput* backpackBtnInput = gameObjectCtrl->addComponent<AQ_CompInput>(backpackBtns, new AQ_CompInput(currentWindow, new unsigned int[0]{},
        new unsigned int[0]{}, backpackButtons::processInputs, inputSystemCtrl), "BackpackButtonInput");
    
    backpackBtns->setCallbackFuncs(backpackButtons::start, backpackButtons::update, backpackButtons::stop);
    // ---------------------------------------------

    // -------- Shop and Clerk Lady ----------------
    AQ_GameObject* shopObject = gameObjectCtrl->createGameObject("ShopObject");
    shopObject->setCallbackFuncs(shop::start, shop::update, shop::stop);

    AQ_CompSimpleBox2D* shopLady = gameObjectCtrl->addComponent<AQ_CompSimpleBox2D>
        (shopObject, new AQ_CompSimpleBox2D(charAndBtnVAO, charAndBtnVBO, charAndBtnEBO, 6), "ShopLady");
    // ---------------------------------------------

    // Set the first scene to mainhall.
    currentScene = CurrentScene::MAINHALL;
    gameObjectCtrl->startGameObjects();
    // @The shader object gets back from gameObject created in start().

    audioSystemCtrl->play2D("assets/Sounds/Musics/Testing/getout.ogg", true);
    while(!glfwWindowShouldClose(currentWindow)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.f, 1.f, 1.f, 1.f);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("Tests1234")) {
                    if (ImGui::MenuItem("Test1", "Test2")) {}
                    if (ImGui::MenuItem("Test1", "Test2")) {}
                    if (ImGui::MenuItem("Test1", "Test2")) {}
                    if (ImGui::MenuItem("Test1", "Test2")) {}
                    if (ImGui::MenuItem("Test3", "Test4")) {}
                    if (ImGui::MenuItem("Test3", "Test4")) {}
                    if (ImGui::MenuItem("Test3", "Test4")) {}
                    if (ImGui::MenuItem("Test3", "Test4")) {}
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Tests2134")) {
                    if (ImGui::MenuItem("Test1", "Test2")) {}
                    if (ImGui::MenuItem("Test1", "Test2")) {}
                    if (ImGui::MenuItem("Test1", "Test2")) {}
                    if (ImGui::MenuItem("Test3", "Test4")) {}
                    if (ImGui::MenuItem("Test3", "Test4")) {}
                    if (ImGui::MenuItem("Test3", "Test4")) {}
                    if (ImGui::MenuItem("Test3", "Test4")) {}
                    if (ImGui::MenuItem("Test3", "Test4")) {}
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Testsasdfsdfa")) {
                    if (ImGui::MenuItem("Test1", "Test2")) {}
                    if (ImGui::MenuItem("Test1", "Test2")) {}
                    if (ImGui::MenuItem("Test1", "Test2")) {}
                    if (ImGui::MenuItem("Test3", "Test4")) {}
                    if (ImGui::MenuItem("Test3", "Test4")) {}
                    if (ImGui::MenuItem("Test3", "Test4")) {}
                    ImGui::EndMenu();
                }
            }
            if (ImGui::Button("Press me!")) {

            }

            //static float f = 0.0f;
            //static int counter = 0;

            //ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            //ImVec2 windowSize(336.f, 210.f);
            //ImGui::SetWindowSize(windowSize);
            //ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ////ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ////ImGui::Checkbox("Another Window", &show_another_window);

            //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ////ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            //    counter++;
            //ImGui::SameLine();
            //ImGui::Text("counter = %d", counter);

            //ImGui::Text("Seconds passed in game: %u", (unsigned int)timeCtrl->getSecondsInGame());
            //ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            //ImGui::End();
        }

        timeCtrl->updateTime();
        inputSystemCtrl->processInputs();
        gameObjectCtrl->updateGameObjects();

        ImGui::Render();
        glfwGetFramebufferSize(currentWindow, &SCR_WIDTH, &SCR_HEIGHT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(currentWindow);
    }
    audioSystemCtrl->stopAllSounds();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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
