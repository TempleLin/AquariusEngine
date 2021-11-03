#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class AQ_Window {
private:
	GLFWwindow* window;
	double mouseX, mouseY;
public:
	AQ_Window(GLFWwindow* window) : window(window), mouseX(0), mouseY(0) {

	}
	double getMouseX() {

	}
	double getMouseY() {

	}
	double getMouseXNormalized() {

	}
	double getMouseYNormalized() {

	}
};