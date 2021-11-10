#include "guiDesign.h"
#include "dear_imgui/imgui.h"
#include "dear_imgui/imgui_impl_glfw.h"
#include "dear_imgui/imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "settingsValues.h"
#include <AQSLTranspilerJNI_ImguiWrap.h>

void guiUpdate();

JNIEXPORT void JNICALL Java_AQSLTranspilerJNI_ImguiWrap_initializeImGUI
(JNIEnv*, jobject, jlong currentWindow) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)currentWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

JNIEXPORT void JNICALL Java_AQSLTranspilerJNI_ImguiWrap_newFrame
(JNIEnv*, jobject) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

JNIEXPORT void JNICALL Java_AQSLTranspilerJNI_ImguiWrap_render
(JNIEnv*, jobject, jlong currentWindow) {
    ImGui::Render();
}

JNIEXPORT void JNICALL Java_AQSLTranspilerJNI_ImguiWrap_renderDrawData
(JNIEnv*, jobject) {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

JNIEXPORT void JNICALL Java_AQSLTranspilerJNI_ImguiWrap_guiUpdate
(JNIEnv*, jobject) {
    guiUpdate();
}

JNIEXPORT void JNICALL Java_AQSLTranspilerJNI_ImguiWrap_shutdown
(JNIEnv*, jobject) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void guiUpdate() {
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
    //ImVec2 windowSize(336.f, 210.f);
    ImGui::SetWindowSize(ImVec2{ static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT) });
    ImGui::SetWindowPos(ImVec2{ 0.f, 0.f });
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

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