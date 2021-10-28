#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "dear_imgui/imgui.h"
#include "dear_imgui/imgui_impl_glfw.h"
#include "dear_imgui/imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <headers/AQ_Shader.hpp>
#include <headers/AQ_CompCamera.hpp>
#include <headers/AQ_CompModel.hpp>
#include <headers/AQ_GameObjectCtrl.hpp>
#include <headers/stbi_image_wrapper.hpp>
#include <headers/AQ_Database.hpp>
#include <headers/AQ_GameObject.hpp>
#include <headers/AQ_GlobalCtrl.hpp>
#include <headers/AQ_CompInput.hpp>
#include <headers/AQ_GLIntegrate.hpp>

#include <iostream>
#include <array>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


//#define REMOVE_GUITAR_IN_SECONDS
#ifdef REMOVE_GUITAR_IN_SECONDS
#define SECONDS_TO_REMOVE_GUITAR 8.f
#endif

namespace read_objmodel {
    using namespace stbi_image_wrap;
    using namespace aquarius_engine;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void countTime();
    void processInput_waitForRebind(GLFWwindow* window, AQ_GameObject** gameObjectsRef,
        AQ_GlobalCtrl::TimeCtrl* timeCtrl, unsigned int* inputKeys, unsigned int* inputActions);
    void processInputCallback(GLFWwindow* window, AQ_GameObject** gameObjectsRef,
        AQ_GlobalCtrl::TimeCtrl* timeCtrl, unsigned int* inputKeys, unsigned int* inputActions);

    // Initializations of AquariusEngine components.
    AQ_Database::Components* databaseComponents= new AQ_Database::Components();
    AQ_Database::GameObjects* databaseGameObjects = new AQ_Database::GameObjects();
    AQ_GameObjectCtrl gameObjectCtrl(databaseComponents, databaseGameObjects);

    AQ_Database::GlobalLights databaseGlobalLights;
    AQ_GlobalCtrl::LightsCtrl lightsCtrl(&databaseGlobalLights);

    AQ_GlobalCtrl::TimeCtrl timeCtrl;
    AQ_GlobalCtrl::InputSystemCtrl inputSystemCtrl(&timeCtrl);

    AQ_OpenGL* aqOpenGL = new AQ_OpenGL();
    GLFWwindow* currentWindow;

    // settings
    int SCR_WIDTH = 1200;
    int SCR_HEIGHT = 900;

    // camera
    AQ_GameObject* cameraObject;
    AQ_CompCamera* camera = nullptr;
    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;
    bool firstMouse = true;

    int callable_main() {
        const char* glsl_version = "#version 330";

        aqOpenGL->setOpenGL()
            .ver_Profile(3, 3, GLFW_OPENGL_CORE_PROFILE)
            .createWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL, true)
            .setFrameBufferSizeCallback(aqOpenGL->getBoundWindow(), framebuffer_size_callback)
            .setCursorPosCallback(aqOpenGL->getBoundWindow(), mouse_callback)
            .setScrollCallback(aqOpenGL->getBoundWindow(), scroll_callback)
            .setInputMode(aqOpenGL->getBoundWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED)
            .setCurrentThreadWindow(aqOpenGL->getWindowByName("LearnOpenGL", 0))
            .initializeGLAD()
            .finishSettings();
        currentWindow = aqOpenGL->getBoundWindow();


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

        // ImGui State
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


        // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
        setFlipVerticallyOnLoad(true);

        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE); //Face culling



        // build and compile shaders
        // -------------------------
        AQ_Shader ourShader("shaders/objModelSimpleShader/shaderVS.glsl", "shaders/objModelSimpleShader/shaderFS.glsl");

        cameraObject = gameObjectCtrl.createGameObject("CAMERA_OBJECT");
        if (!cameraObject)
            std::cout << "NULL" << std::endl;
        camera =gameObjectCtrl.addComponent<AQ_CompCamera>(cameraObject, new AQ_CompCamera(glm::vec3(0.f, 0.f, 3.f)), "CAMERA");

        AQ_CompInput* cameraInput = gameObjectCtrl.addComponent<AQ_CompInput>(cameraObject,
            new AQ_CompInput(currentWindow, new AQ_GameObject * [1]{cameraObject},
                new unsigned int[7]{ GLFW_KEY_ESCAPE, GLFW_KEY_A, GLFW_KEY_W, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_E, GLFW_KEY_Q},
                    new unsigned int[1]{ GLFW_PRESS }, processInput_waitForRebind, inputSystemCtrl), "CameraInput");

        cameraInput->rebindInputKeys(new unsigned int[7]{ GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_E, GLFW_KEY_Q });

        // load models
        // -----------
        AQ_GameObject* guitarObject = gameObjectCtrl.createGameObject("GUITAR_OBJECT");
        AQ_CompModel* guitarModel = gameObjectCtrl.addComponent<AQ_CompModel>(guitarObject, new AQ_CompModel("resources/objects/backpack/backpack.obj"), "GUITAR");
        
        
        // draw in wireframe
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // render loop
        // -----------
        while (!glfwWindowShouldClose(currentWindow)) {

            // Poll and handle events (inputs, window resize, etc.)
            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
            glfwPollEvents();

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
                ImVec2 windowSize(336.f, 210.f);
                ImGui::SetWindowSize(windowSize);
                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);

                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Seconds passed in game: %u", (unsigned int)timeCtrl.getSecondsInGame());
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window) {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                if (ImGui::Button("Close Me"))
                    show_another_window = false;
                ImGui::End();
            }

            // Count deltaTime and seconds in game.
            //countTime();
            timeCtrl.updateTime();

            // Delete guitar in 8 seconds.
            static bool deletedGuitar{ false };
            if (!deletedGuitar && timeCtrl.getSecondsInGame() > 8) {
                gameObjectCtrl.deleteGameObject("GUITAR_OBJECT");
                deletedGuitar = true;
            }

            // input
                // -----
            //processInput(window);
            inputSystemCtrl.processInputs();


            // render
            // ------
            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // don't forget to enable shader before setting uniforms
            ourShader.use();

            // view/projection transformations
            glm::mat4 projection = glm::perspective(glm::radians(camera->zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            glm::mat4 view = camera->getViewMatrix();
            ourShader.setMat4("projection", projection);
            ourShader.setMat4("view", view);


            // render the loaded model
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(.5f, .5f, .5f));	// it's a bit too big for our scene, so scale it down
            ourShader.setMat4("model", model);
            if (guitarModel)
                guitarModel->draw(ourShader);

#ifdef REMOVE_GUITAR_IN_SECONDS
#if defined(SECONDS_TO_REMOVE_GUITAR)
            if (timeCtrl.getSecondsInGame() > SECONDS_TO_REMOVE_GUITAR)
                AQ_GameObjectCtrl::removeComponent<AQ_CompModel>(guitarObject, "GUITAR");
#else
            if (timeCtrl.getSecondsInGame() > 10.f)
                AQ_GameObjectCtrl::removeComponent<AQ_CompModel>(guitarObject, "GUITAR");
#endif
#endif
            // Rendering
            ImGui::Render();
            glfwGetFramebufferSize(currentWindow, &SCR_WIDTH, &SCR_HEIGHT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // glfw: swap buffers
            // -------------------------------------------------------------------------------
            //glfwSwapBuffers(window);
            glfwSwapBuffers(currentWindow);
        }



        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        delete databaseComponents;
        delete databaseGameObjects;
        delete aqOpenGL;
        glfwTerminate();
        return 0;
    }

    // glfw: whenever the window size changed (by OS or user resize) this callback function executes
    // ---------------------------------------------------------------------------------------------
    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        glViewport(0, 0, width, height);
    }

    // glfw: whenever the mouse moves, this callback is called
    // -------------------------------------------------------
    void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera->processMouseMovement(xoffset, yoffset);
    }

    // glfw: whenever the mouse scroll wheel scrolls, this callback is called
    // ----------------------------------------------------------------------
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
        camera->processMouseScroll(yoffset);
    }

    void processInput_waitForRebind(GLFWwindow* window, AQ_GameObject** gameObjectsRef,
        AQ_GlobalCtrl::TimeCtrl* timeCtrl, unsigned int* inputKeys, unsigned int* inputActions) {
       AQ_CompInput* _cameraInput = gameObjectCtrl.getComponent<AQ_CompInput>(gameObjectsRef[0], "CameraInput");
        std::cout << timeCtrl->getSecondsInGame() << "\n";
        if (timeCtrl->getSecondsInGame() >= 3.f)
            _cameraInput->rebindCallBack(processInputCallback);
        std::cout << "Wait for few seconds until rebind" << "\n";
    }

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInputCallback(GLFWwindow* window, AQ_GameObject** gameObjectsRef,
        AQ_GlobalCtrl::TimeCtrl* timeCtrl, unsigned int* inputKeys, unsigned int* inputActions) {

        static AQ_CompCamera* _camera = gameObjectCtrl.getComponent<AQ_CompCamera>(gameObjectsRef[0], "CAMERA");

        if (glfwGetKey(window, inputKeys[0]) == inputActions[0])
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, inputKeys[1]) == inputActions[0])
            _camera->processKeyboard(ECameraMovement::FORWARD, timeCtrl->getDeltaTime());
        if (glfwGetKey(window, inputKeys[2]) == inputActions[0])
            _camera->processKeyboard(ECameraMovement::LEFT, timeCtrl->getDeltaTime());
        if (glfwGetKey(window, inputKeys[3]) == inputActions[0])
            _camera->processKeyboard(ECameraMovement::BACKWARD, timeCtrl->getDeltaTime());
        if (glfwGetKey(window, inputKeys[4]) == inputActions[0])
            _camera->processKeyboard(ECameraMovement::RIGHT, timeCtrl->getDeltaTime());
        if (glfwGetKey(window, inputKeys[5]) == inputActions[0])
            _camera->processKeyboard(ECameraMovement::UP, timeCtrl->getDeltaTime());
        if (glfwGetKey(window, inputKeys[6]) == inputActions[0])
            _camera->processKeyboard(ECameraMovement::DOWN, timeCtrl->getDeltaTime());
    }
}