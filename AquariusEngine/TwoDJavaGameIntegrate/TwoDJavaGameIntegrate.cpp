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
#include <headers/AQ_CompBoxInventory2D.hpp>

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
#include "headers/mainhallCallbacks.h"
#include "headers/PassingValues.hpp"
#include "headers/backpackButtonsCallbacks.h"
#include "headers/shopCallbacks.h"
#include "headers/attackCallbacks.h"
#include "headers/missionCallbacks.h"
#include "headers/backpackCallbacks.h"


using namespace aquarius_engine;
using namespace stbi_image_wrap;

void glfwError(int id, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

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


    AQ_Shader theShader("assets/shaders/two_d_tex_vs.glsl", "assets/shaders/two_d_tex_fs.glsl");

    // -------- Create background-------------------
    AQ_GameObject* mainhallObject = gameObjectCtrl->createGameObject("MainhallObject");
    AQ_CompSimpleBox2D* background2D = gameObjectCtrl->
        addComponent<AQ_CompSimpleBox2D>(mainhallObject, new AQ_CompSimpleBox2D(theShader.ID), "Mainhall2D");
    mainhallObject->setCallbackFuncs(mainhall::start, mainhall::update, mainhall::stop);
    // ---------------------------------------------

    // -------- Create main character --------------
    AQ_GameObject* mainCharacter = gameObjectCtrl->createGameObject("MainCharacter");

    AQ_CompSimpleBox2D* mainChar2D = gameObjectCtrl->
        addComponent<AQ_CompSimpleBox2D>(mainCharacter, new AQ_CompSimpleBox2D(theShader.ID), "MainCharacter2D");
    mainChar2D->keepAspectRatio();
    mainCharacter->setCallbackFuncs(mainCharacter::start, mainCharacter::update, mainCharacter::stop);
    // ---------------------------------------------

    // -------- Shortcut buttons -------------------
    AQ_GameObject* shortcutBtns = gameObjectCtrl->createGameObject("ShortcutButtons");

    CustomButtonComp* mainhallBtn = gameObjectCtrl->addComponent<CustomButtonComp>(shortcutBtns,
        new CustomButtonComp(theShader.ID), "MainHallButton2D");
    CustomButtonComp* missionBtn = gameObjectCtrl->addComponent<CustomButtonComp>(shortcutBtns,
        new CustomButtonComp(theShader.ID), "MissionButton2D");
    CustomButtonComp* attackBtn = gameObjectCtrl->addComponent<CustomButtonComp>(shortcutBtns,
        new CustomButtonComp(theShader.ID), "AttackButton2D");
    CustomButtonComp* shopBtn = gameObjectCtrl->addComponent<CustomButtonComp>(shortcutBtns,
        new CustomButtonComp(theShader.ID), "ShopButton2D");
    CustomButtonComp* statusBtn = gameObjectCtrl->addComponent<CustomButtonComp>(shortcutBtns,
        new CustomButtonComp(theShader.ID), "StatusButton2D");

    AQ_CompInput* shortcutInput = gameObjectCtrl->addComponent<AQ_CompInput>(shortcutBtns, new AQ_CompInput(currentWindow, new unsigned int[1]{ GLFW_KEY_A },
        new unsigned int[1]{ GLFW_PRESS }, shortcutButton::processInputs, inputSystemCtrl), "ShortcutButtonInput");
    shortcutBtns->setCallbackFuncs(shortcutButton::start, shortcutButton::update, shortcutButton::stop);
    // ---------------------------------------------

    // -------- Backpack ---------------------------
    AQ_GameObject* backpackObject = gameObjectCtrl->createGameObject("BackpackObject");
    AQ_CompBoxInventory2D* backpack2D = gameObjectCtrl->addComponent<AQ_CompBoxInventory2D>(backpackObject, new AQ_CompBoxInventory2D(theShader.ID, true, 100), "Backpack2D");
    backpackObject->setCallbackFuncs(backpack::start, backpack::update, backpack::stop);
    // ---------------------------------------------

    // -------- Backpack button ---------------------
    AQ_GameObject* backpackBtns = gameObjectCtrl->createGameObject("BackpackButtons");

    CustomButtonComp* backPackClotheBtn = gameObjectCtrl->addComponent<CustomButtonComp>(backpackBtns,
        new CustomButtonComp(theShader.ID), "BackpackClotheBtn2D");

    CustomButtonComp* backPackWeaponsBtn = gameObjectCtrl->addComponent<CustomButtonComp>(backpackBtns,
        new CustomButtonComp(theShader.ID), "BackpackWeaponsBtn2D");

    AQ_CompInput* backpackBtnInput = gameObjectCtrl->addComponent<AQ_CompInput>(backpackBtns, new AQ_CompInput(currentWindow, new unsigned int[0]{},
        new unsigned int[0]{}, backpackButtons::processInputs, inputSystemCtrl), "BackpackButtonInput");
    
    backpackBtns->setCallbackFuncs(backpackButtons::start, backpackButtons::update, backpackButtons::stop);
    // ---------------------------------------------

    // -------- Shop and Clerk Lady ----------------
    AQ_GameObject* shopObject = gameObjectCtrl->createGameObject("ShopObject");
    shopObject->setCallbackFuncs(shop::start, shop::update, shop::stop);

    AQ_CompSimpleBox2D* shopBackground = gameObjectCtrl->addComponent<AQ_CompSimpleBox2D>
        (shopObject, new AQ_CompSimpleBox2D(theShader.ID), "ShopBackground");
    AQ_CompSimpleBox2D* clerk = gameObjectCtrl->addComponent<AQ_CompSimpleBox2D>
        (shopObject, new AQ_CompSimpleBox2D(theShader.ID), "Clerk");
    AQ_CompSimpleBox2D* coin = gameObjectCtrl->addComponent<AQ_CompSimpleBox2D>
        (shopObject, new AQ_CompSimpleBox2D(theShader.ID), "Coin");
    // ---------------------------------------------

    // -------- Attack Page-------------------------
    AQ_GameObject* attackObject = gameObjectCtrl->createGameObject("AttackObject");
    attackObject->setCallbackFuncs(attack::start, attack::update, attack::stop);
    AQ_CompInput* attackInput = gameObjectCtrl->addComponent<AQ_CompInput>(attackObject, new AQ_CompInput(currentWindow, new unsigned int[0]{},
        new unsigned int[0]{}, attack::processInputs, inputSystemCtrl), "BackpackButtonInput");
    AQ_CompSimpleBox2D* attackSelectionPage = gameObjectCtrl->addComponent<AQ_CompSimpleBox2D>
        (attackObject, new AQ_CompSimpleBox2D(theShader.ID), "AttackSelectionPage");
    CustomButtonComp* selectionMonsterBtn0 = gameObjectCtrl->addComponent<CustomButtonComp>(attackObject,
        new CustomButtonComp(theShader.ID), "SelectionMonsterBtn0");
    CustomButtonComp* selectionMonsterBtn1 = gameObjectCtrl->addComponent<CustomButtonComp>(attackObject,
        new CustomButtonComp(theShader.ID), "SelectionMonsterBtn1");

    AQ_CompSimpleBox2D* succubus = gameObjectCtrl->addComponent<AQ_CompSimpleBox2D>(attackObject, 
        new AQ_CompSimpleBox2D(theShader.ID), "Succubus2D");
    // ---------------------------------------------
     
    // -------- Mission Page------------------------
    AQ_GameObject* missionObject = gameObjectCtrl->createGameObject("MissionObject");
    missionObject->setCallbackFuncs(mission::start, mission::update, mission::stop);
    AQ_CompSimpleBox2D* missionBoard = gameObjectCtrl->addComponent<AQ_CompSimpleBox2D>
        (missionObject, new AQ_CompSimpleBox2D(theShader.ID), "MissionBoard");
    // ---------------------------------------------
   
    // Set the first scene to mainhall.
    currentScene = CurrentScene::MAINHALL;
    gameObjectCtrl->startGameObjects();
    // @The shader object gets back from gameObject created in start().

    audioSystemCtrl->play2D("assets/Sounds/Musics/Locations_Shop_Loop_Stem2_Strings.wav", true);
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
}