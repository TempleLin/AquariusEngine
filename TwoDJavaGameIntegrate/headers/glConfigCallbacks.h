#pragma once
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
class MousePosCallback {
private:
    static double _xpos;
    static double _ypos;
public:
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    double getXPos();
    double getYPos();
};

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void glfwError(int id, const char* description);