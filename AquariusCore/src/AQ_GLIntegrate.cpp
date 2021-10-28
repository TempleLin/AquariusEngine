#include "headers/AQ_GLIntegrate.hpp"

namespace aquarius_engine {
	AQ_OpenGL::AQ_OpenGL() {
		settings = nullptr;
		boundWindow = nullptr;
	}

	AQ_OpenGL::Settings& AQ_OpenGL::setOpenGL() {
		if (!settings)
			settings = new Settings(this);
		return *settings;
	}

	void AQ_OpenGL::bindWindow(GLFWwindow* window) {
		this->boundWindow = window;
	}

	void AQ_OpenGL::unbindWindow() {
		this->boundWindow = nullptr;
	}

	GLFWwindow* AQ_OpenGL::getWindowByName(const char* name, unsigned int indexOfSameName) {
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

	GLFWwindow* AQ_OpenGL::getBoundWindow() {
		return this->boundWindow;
	}

	AQ_OpenGL::~AQ_OpenGL() {
		if (settings)
			delete settings;
		for (int i = 0; i < windows.size(); i++) {
			delete windows.at(i);
		}
		windows.clear();
		std::cout << "OpenGL deleted\n";
	}

	AQ_OpenGL::WindowNamePair::WindowNamePair(GLFWwindow* window, std::string name) {
		this->window = window;
		this->name = name;
	}

	AQ_OpenGL::WindowNamePair::~WindowNamePair() {
		glfwDestroyWindow(window);
		std::cout << "Window pair deleted\n";
	}

	AQ_OpenGL::Settings::Settings(AQ_OpenGL* openGL) {
		this->aq_OpenGL = openGL;
	}

	AQ_OpenGL::Settings& AQ_OpenGL::Settings::ver_Profile
		(unsigned int major, unsigned int minor, unsigned int PROFILE, void (*errorCallback)(int, const char*)) {
		glfwSetErrorCallback(errorCallback);
		if (!glfwInit()) {
			std::cout << "glfw did not initialize!" << std::endl;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		return *this;
	}

	AQ_OpenGL::Settings& AQ_OpenGL::Settings::createWindow(unsigned int width, unsigned int height, 
		const char* windowName, GLFWmonitor* monitor, GLFWwindow* share, bool bindWindow) {
		GLFWwindow* windowCreated = glfwCreateWindow(width, height, windowName, monitor, share);
		if (windowCreated) {
			aq_OpenGL->windows.push_back(new WindowNamePair(windowCreated, windowName));
			std::cout << "Window: " << windowName << " created at address: " << windowCreated << "\n";
		} else {
			std::cout << "ERROR: Failed to create GLFW window with name: " << windowName << std::endl;
			glfwTerminate();
		}
		if (bindWindow)
			aq_OpenGL->boundWindow = windowCreated;
		return *this;
	}

	AQ_OpenGL::Settings& AQ_OpenGL::Settings::setCurrentThreadWindow(GLFWwindow* window) {
		glfwMakeContextCurrent(window);
		return *this;
	}

	AQ_OpenGL::Settings& AQ_OpenGL::Settings::initializeGLAD() {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
		}
		return *this;
	}

	AQ_OpenGL::Settings& AQ_OpenGL::Settings::setFrameBufferSizeCallback
	(GLFWwindow* window, void(*callbackFunc)(GLFWwindow*, int, int)) {
		glfwSetFramebufferSizeCallback(window, callbackFunc);
		return *this;
	}

	AQ_OpenGL::Settings& AQ_OpenGL::Settings::setCursorPosCallback(GLFWwindow* window,
		void(*callbackFunc)(GLFWwindow*, double, double)) {
		glfwSetCursorPosCallback(window, callbackFunc);
		return *this;
	}

	AQ_OpenGL::Settings& AQ_OpenGL::Settings::setScrollCallback
	(GLFWwindow* window, void(*callbackFunc)(GLFWwindow*, double, double)) {
		glfwSetScrollCallback(window, callbackFunc);
		return *this;
	}

	AQ_OpenGL::Settings& AQ_OpenGL::Settings::setInputMode(GLFWwindow* window, int mode, int value) {
		// tell GLFW to capture our mouse
		glfwSetInputMode(window, mode, value);
		return *this;
	}

	void AQ_OpenGL::Settings::finishSettings() {
		aq_OpenGL->settings = nullptr;
		delete this;
	}
}
