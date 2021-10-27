#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>

class AQ_OpenGL {
private:
	class WindowNamePair {
	public:
		GLFWwindow* window;
		std::string name;
		WindowNamePair(GLFWwindow* window, std::string name) {
			this->window = window;
			this->name = name;
		}
		~WindowNamePair() {
			delete window;
			std::cout << "Window pair deleted\n";
		}
	};
	class Settings {
	public:
		AQ_OpenGL* aq_OpenGL;
		Settings(AQ_OpenGL* openGL) {
			this->aq_OpenGL = openGL;
		}
		Settings& ver_Profile(unsigned int major, unsigned int minor, unsigned int PROFILE) {
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
			glfwWindowHint(GLFW_OPENGL_PROFILE, PROFILE);
			return *this;
		}
		Settings& createWindow(unsigned int width, unsigned int height, const char* windowName,
			GLFWmonitor* monitor, GLFWwindow *share) {
			GLFWwindow* windowCreated = glfwCreateWindow(width, height, windowName, monitor, share);
			if (windowCreated) {
				aq_OpenGL->windows.push_back(new WindowNamePair(windowCreated, windowName));
			} else {
				std::cout << "ERROR: Failed to create GLFW window with name: " << windowName << std::endl;
				glfwTerminate();
			}
			return *this;
		}
		Settings& setCurrentThreadWindow(GLFWwindow* window) {
			glfwMakeContextCurrent(window);
			return *this;
		}
		void initializeGLAD() {
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				std::cout << "Failed to initialize GLAD" << std::endl;
			}
		}
	};
	Settings* settings;
	std::vector<WindowNamePair*> windows;

public:
	AQ_OpenGL() {
		settings = new Settings(this);
	}
	Settings& setOpenGL() {
		glfwInit();
		return *settings;
	}
	GLFWwindow* getWindowByName(const char* name, unsigned int indexOfSameName) {
		for (int i = 0; i < windows.size(); i++) {
			if (windows.at(i)->name == name) {
				if (!indexOfSameName) {
					return windows.at(i)->window;
				} else {
					indexOfSameName--;
				}
			}
		}
		std::cout << "ERROR: CANNOT GET WINDOW BY NAME: " << name << "\n";
		return nullptr;
	}

	~AQ_OpenGL() {
		delete settings;
		for (int i = 0; i < windows.size(); i++) {
			delete windows.at(i);
		}
		windows.clear();
		std::cout << "OpenGL deleted\n";
	}
};