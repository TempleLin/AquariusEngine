#include "../../JAquariusEngine/EngineCore_AQ_DearImGUI.h"
#include "dear_imgui/imgui.h"
#include "dear_imgui/imgui_impl_glfw.h"
#include "dear_imgui/imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_intializeImGUI
(JNIEnv* env, jobject, jlong currentWindow, jstring glslVersion) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)currentWindow, true);

    jboolean isCopy;
    const char* _glslVersion = env->GetStringUTFChars(glslVersion, &isCopy);
    ImGui_ImplOpenGL3_Init(_glslVersion);
    if (isCopy == JNI_TRUE) {
        env->ReleaseStringUTFChars(glslVersion, _glslVersion);
    }
}

JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_newFrame
(JNIEnv*, jobject) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_render
(JNIEnv*, jobject) {
    ImGui::Render();
}

JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_renderDrawData
(JNIEnv*, jobject) {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_shutDown
(JNIEnv*, jobject) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_begin
(JNIEnv* env, jobject, jstring windowName) {
    jboolean isCopy;
    const char* _windowName = env->GetStringUTFChars(windowName, &isCopy);
    ImGui::Begin(_windowName);
    if (isCopy == JNI_TRUE) {
        env->ReleaseStringUTFChars(windowName, _windowName);
    }
}

JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_setWindowSize
(JNIEnv*, jobject, jfloat width, jfloat height) {
    ImGui::SetWindowSize(ImVec2{ width, height });
}

JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_setWindowPos
(JNIEnv*, jobject, jfloat x, jfloat y) {
    ImGui::SetWindowPos(ImVec2{ x, y });
}

JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_text
(JNIEnv* env, jobject, jstring textContent) {
    jboolean isCopy;
    const char* _textContent = env->GetStringUTFChars(textContent, &isCopy);
    ImGui::Text(_textContent);
    if (isCopy == JNI_TRUE) {
        env->ReleaseStringUTFChars(textContent, _textContent);
    }
}

JNIEXPORT jfloat JNICALL Java_EngineCore_AQ_1DearImGUI_sliderFloat
(JNIEnv* env, jobject, jstring label, jfloat minValue, jfloat maxValue) {
    jboolean isCopy;
    const char* _label = env->GetStringUTFChars(label, &isCopy);
    float floatValue;
    ImGui::SliderFloat(_label, &floatValue, minValue, maxValue);
    if (isCopy == JNI_TRUE) {
        env->ReleaseStringUTFChars(label, _label);
    }
    return floatValue;
}

JNIEXPORT jfloatArray JNICALL Java_EngineCore_AQ_1DearImGUI_colorEdit3
(JNIEnv* env, jobject, jstring label) {
    jboolean isCopy;
    const char* _label = env->GetStringUTFChars(label, &isCopy);

    ImVec4 values;
    ImGui::ColorEdit3(_label, (float*)&values);

    if (isCopy == JNI_TRUE) {
        env->ReleaseStringUTFChars(label, _label);
    }

    jfloatArray returnFArray = env->NewFloatArray(jsize(4));
    env->SetFloatArrayRegion(returnFArray, 0, jsize(4), (float*)&values);
    return returnFArray;
}

JNIEXPORT jboolean JNICALL Java_EngineCore_AQ_1DearImGUI_button
(JNIEnv* env, jobject, jstring label) {
    jboolean isCopy;
    const char* _label = env->GetStringUTFChars(label, &isCopy);

    bool pressed = ImGui::Button(_label);

    if (isCopy == JNI_TRUE) {
        env->ReleaseStringUTFChars(label, _label);
    }

    return pressed;
}

JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_sameLine
(JNIEnv*, jobject) {
    ImGui::SameLine();
}

JNIEXPORT void JNICALL Java_EngineCore_AQ_1DearImGUI_end
(JNIEnv*, jobject) {
    ImGui::End();
}