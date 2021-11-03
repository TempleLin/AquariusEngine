#include "headers/glConfigCallbacks.h"
#include "headers/TwoDJavaGameIntegrate.hpp"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}

double MousePosCallback::_xpos{};
double MousePosCallback::_ypos{};

void MousePosCallback::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    //if (firstMouse) {
    //    lastX = xpos;
    //    lastY = ypos;
    //    firstMouse = false;
    //}

    //float xoffset = xpos - lastX;
    //float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    //lastX = xpos;
    //lastY = ypos;

    //camera->processMouseMovement(xoffset, yoffset);
    _xpos = xpos;
    _ypos = ypos;
}

double MousePosCallback::getXPos() {
    return _xpos;
}

double MousePosCallback::getYPos() {
    return _ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    //camera->processMouseScroll(yoffset);
}

void glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}