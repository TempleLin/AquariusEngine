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

#include <headers/AQ_Shader.h>
#include <headers/AQ_CompCamera.h>
#include <headers/AQ_CompModel.h>
#include <headers/AQ_GameObjectCtrl.h>
#include <headers/stbi_image_wrapper.h>
#include <headers/AQ_Database.h>
#include <headers/AQ_GameObject.h>
#include <headers/AQ_GlobalCtrl.h>
#include <headers/AQ_CompInput.h>

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

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void processInput(GLFWwindow* window);
    void countTime();

    // Initializations of AquariusEngine components.
    AQ_Database::Components databaseComponents;
    AQ_GameObjectCtrl gameObjectCtrl(databaseComponents);

    AQ_Database::GlobalLights databaseGlobalLights;
    AQ_GlobalCtrl::LightsCtrl lightsCtrl(databaseGlobalLights);

    AQ_GlobalCtrl::InputSystemCtrl inputSystemCtrl;

    // settings
    int SCR_WIDTH = 1200;
    int SCR_HEIGHT = 900;

    // camera
    AQ_GameObject cameraObject(gameObjectCtrl);
    AQ_CompCamera* camera = nullptr;
    float lastX = SCR_WIDTH / 2.0f;
    float lastY = SCR_HEIGHT / 2.0f;
    bool firstMouse = true;

    // timing
    float deltaTime{ 0.f };
    float lastFrame{ 0.f };
    float secondsFloatCount{ 0.f };

    int callable_main() {
        // glfw: initialize and configure
        // ------------------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        const char* glsl_version = "#version 330";

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        // --------------------
        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
        if (window == NULL) {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

        // tell GLFW to capture our mouse
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
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
        ImGui_ImplGlfw_InitForOpenGL(window, true);
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

        gameObjectCtrl.addComponent<AQ_CompCamera>(cameraObject, AQ_CompCamera(glm::vec3(0.f, 0.f, 3.f)), "CAMERA");
        camera = &(gameObjectCtrl.getComponent<AQ_CompCamera>(cameraObject, "CAMERA"));

        gameObjectCtrl.addComponent<AQ_CompInput>(cameraObject, AQ_CompInput(&std::array<AQ_GameObject*, 1>{&cameraObject}[0], new 
            std::function<void()>([]() { std::cout << "Test Input" << "\n"; }), inputSystemCtrl), "CameraInput");

        AQ_CompInput cameraInput = gameObjectCtrl.getComponent<AQ_CompInput>(cameraObject, "CameraInput");
        (*cameraInput.processInputs)();

        // load models
        // -----------
        AQ_GameObject guitarObject(gameObjectCtrl);
        gameObjectCtrl.addComponent<AQ_CompModel>(guitarObject, AQ_CompModel("resources/objects/backpack/backpack.obj"), "GUITAR");
        AQ_CompModel* guitarModel = &(gameObjectCtrl.getComponent<AQ_CompModel>(guitarObject, "GUITAR"));
        

        
        // draw in wireframe
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // render loop
        // -----------
        while (!glfwWindowShouldClose(window)) {

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

                ImGui::Text("Seconds passed in game: %u", (unsigned int)secondsFloatCount);
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
            countTime();

            // input
                // -----
            processInput(window);
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
            if (secondsFloatCount > SECONDS_TO_REMOVE_GUITAR)
                AQ_GameObjectCtrl::removeComponent<AQ_CompModel>(guitarObject, "GUITAR");
#else
            if (secondsCounter > 10.f)
                AQ_GameObjectCtrl::removeComponent<AQ_CompModel>(guitarObject, "GUITAR");
#endif
#endif
            // Rendering
            ImGui::Render();
            glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_HEIGHT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // glfw: swap buffers
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
        }

        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    }

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    // ---------------------------------------------------------------------------------------------------------
    void processInput(GLFWwindow* window) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera->processKeyboard(ECameraMovement::FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera->processKeyboard(ECameraMovement::BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera->processKeyboard(ECameraMovement::LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera->processKeyboard(ECameraMovement::RIGHT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            camera->processKeyboard(ECameraMovement::UP, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            camera->processKeyboard(ECameraMovement::DOWN, deltaTime);
    }

    void countTime() {
        // per-frame time logic
            // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // Count seconds using deltaTime
        secondsFloatCount += deltaTime;
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
}