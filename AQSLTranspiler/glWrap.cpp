#include <iostream>

#include "settingsValues.h"
#include "./AQSLTranspilerJNI/GLWrap.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <headers/AQ_GLIntegrate.hpp>

using namespace aquarius_engine;

void _glfwError(int id, const char* description);
void _framebuffer_size_callback(GLFWwindow* window, int width, int height);

AQ_OpenGL* aqOpenGL = new AQ_OpenGL();

JNIEXPORT void JNICALL Java_GLWrap_defaultOpenGLSettings
(JNIEnv*, jobject) {
    aqOpenGL->setOpenGL()
        .ver_Profile(3, 3, GLFW_OPENGL_CORE_PROFILE, &_glfwError, _glfwError);
}

JNIEXPORT jlong JNICALL Java_GLWrap_createWindow
(JNIEnv* env, jobject, jstring windowName, jint width, jint height) {
    jboolean isCopy;
    const char* stringPointer = env->GetStringUTFChars(windowName, &isCopy);

    aqOpenGL->setOpenGL()
        .createWindow(SCR_WIDTH, SCR_HEIGHT, stringPointer, NULL, NULL, true)
        .setFrameBufferSizeCallback(aqOpenGL->getBoundWindow(), _framebuffer_size_callback)
        .setCurrentThreadWindow(aqOpenGL->getBoundWindow())
        .initializeGLAD()
        .finishSettings();
    GLFWwindow* currentWindow = aqOpenGL->getBoundWindow();
    return (jlong)currentWindow;

    std::cout << "Created window: " << windowName << "\n";
    if (isCopy == JNI_TRUE) {
        env->ReleaseStringUTFChars(windowName, stringPointer);
    }
}

JNIEXPORT jboolean JNICALL Java_GLWrap_glfwWindowShouldClose
(JNIEnv*, jobject, jlong currentWindow) {
    return glfwWindowShouldClose((GLFWwindow*)currentWindow);
}

JNIEXPORT void JNICALL Java_GLWrap_glfwPollEvents
(JNIEnv*, jobject) {
    glfwPollEvents();
}

JNIEXPORT void JNICALL Java_GLWrap_glClearColor
(JNIEnv*, jobject, jfloat r, jfloat g, jfloat b, jfloat a) {
    glClearColor(r, g, b, a);
}

JNIEXPORT void JNICALL Java_GLWrap_glClearColorDepthBuffer
(JNIEnv*, jobject) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

JNIEXPORT void JNICALL Java_GLWrap_glfwSwapBuffers
(JNIEnv*, jobject, jlong currentWindow) {
    glfwSwapBuffers((GLFWwindow*)currentWindow);
}

JNIEXPORT void JNICALL Java_GLWrap_glfwTerminate
(JNIEnv*, jobject) {
    glfwTerminate();
}

JNIEXPORT void JNICALL Java_GLWrap_deleteGL
(JNIEnv*, jobject) {
    delete aqOpenGL;
}



void _glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}

void _framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}