#include <iostream>

#include "dear_imgui/imgui.h"
#include "dear_imgui/imgui_impl_glfw.h"
#include "dear_imgui/imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <headers/AQ_GLIntegrate.hpp>
#include <headers/AQ_GameObjectCtrl.hpp>
#include <headers/AQ_GameObject.hpp>
#include <headers/AQ_CompBoxButton2D.hpp>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

enum class AQSLShaderType {
	SimpleBox2D
};

using namespace aquarius_engine;

const char* glsl_version = "#version 330";
int SCR_WIDTH{ 1600 }, SCR_HEIGHT{ 900 };

void glfwError(int id, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    AQ_OpenGL* aqOpenGL = new AQ_OpenGL();
    GLFWwindow* currentWindow;

    aqOpenGL->setOpenGL()
        .ver_Profile(3, 3, GLFW_OPENGL_CORE_PROFILE, &glfwError, glfwError)
        .createWindow(SCR_WIDTH, SCR_HEIGHT, "AQSLTranspiler", NULL, NULL, true)
        .setFrameBufferSizeCallback(aqOpenGL->getBoundWindow(), framebuffer_size_callback)
        //.setCursorPosCallback(aqOpenGL->getBoundWindow(), mouse_callback)
        //.setScrollCallback(aqOpenGL->getBoundWindow(), scroll_callback)
        //.setInputMode(aqOpenGL->getBoundWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED)
        .setCurrentThreadWindow(aqOpenGL->getBoundWindow())
        .initializeGLAD()
        .finishSettings();
    currentWindow = aqOpenGL->getBoundWindow();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(currentWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(currentWindow)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
            //ImVec2 windowSize(336.f, 210.f);
            ImGui::SetWindowSize(ImVec2{static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT)});
            ImGui::SetWindowPos(ImVec2{ 0.f, 0.f });
            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            //ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            //ImGui::Text("Seconds passed in game: %u", (unsigned int)timeCtrl->getSecondsInGame());
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();

        }

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui::Render();
        glfwGetFramebufferSize(currentWindow, &SCR_WIDTH, &SCR_HEIGHT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(currentWindow);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}