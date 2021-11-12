#include "guiDesign.h"
#include "dear_imgui/imgui.h"
#include <dear_imgui/imgui_internal.h>
#include "dear_imgui/imgui_impl_glfw.h"
#include "dear_imgui/imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <vector>

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

ShaderStrBuffer shaderStrBuffer;
void guiUpdate() {
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Top Section");                          // Create a window called "Hello, world!" and append into it.
    ImGui::SetWindowSize(ImVec2{ static_cast<float>(SCR_WIDTH), static_cast<float>(SCR_HEIGHT)});
    ImGui::SetWindowPos(ImVec2{ 0.f, 0.f });

    ImGui::Text(shaderStrBuffer.topMainBottom[0].c_str());
    ImGui::NewLine();
    char topSection[2550];
    ImGui::InputTextMultiline("Top Section Input", topSection, sizeof(topSection), ImVec2{ (float)SCR_WIDTH, (float) SCR_HEIGHT / 4.f });

    ImGui::Text(shaderStrBuffer.topMainBottom[1].substr(0, shaderStrBuffer.topMainBottom[1].size() - 2).c_str());
    char premainSection[2550];
    ImGui::InputTextMultiline("Pre Main Section Input", premainSection, sizeof(premainSection), ImVec2{ (float)SCR_WIDTH, (float)SCR_HEIGHT / 4.f });
    ImGui::End();

    char bottomSection[25500];

    //std::cout << inputtedText << "\n";

    //ImGui::Text("Seconds passed in game: %u", (unsigned int)timeCtrl->getSecondsInGame());
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}