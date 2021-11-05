#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <string>
#include <vector>
#include <iostream>
namespace aquarius_engine {
	class AQ_OpenGL {
	private:
		class WindowWithInfo {
		public:
			GLFWwindow* window;
			std::string name;
			WindowWithInfo(GLFWwindow* window, std::string name);
			~WindowWithInfo();
		};
		class Settings {
		public:
			AQ_OpenGL* aq_OpenGL;

			Settings(AQ_OpenGL* openGL);
			Settings& ver_Profile(unsigned int major, unsigned int minor, unsigned int PROFILE, 
				void (*errorCallback)(int, const char*), bool enableAlpha);

			Settings& createWindow(unsigned int width, unsigned int height, const char* windowName, 
				GLFWmonitor* monitor, GLFWwindow* share, bool bindWindow);
			Settings& setCurrentThreadWindow(GLFWwindow* window);

			Settings& initializeGLAD();

			Settings& setFrameBufferSizeCallback(GLFWwindow* window, void(*callbackFunc)(GLFWwindow*, int, int));
			Settings& setMouseButtonCallback(GLFWwindow* window, void(*callbackFunc)(GLFWwindow* window, int button, int action, int modes));
			Settings& setCursorPosCallback(GLFWwindow* window, void(*callbackFunc)(GLFWwindow*, double, double));
			Settings& setScrollCallback(GLFWwindow* window, void(*callbackFunc)(GLFWwindow*, double, double));
			Settings& setInputMode(GLFWwindow* window, int mode, int value);

			void finishSettings();
		};
		Settings* settings;
		std::vector<WindowWithInfo*> windows;
		GLFWwindow* boundWindow;
	public:
		AQ_OpenGL();
		Settings& setOpenGL();
		void bindWindow(GLFWwindow* window);
		void unbindWindow();
		GLFWwindow* getWindowByName(const char* name, unsigned int indexOfSameName);
		GLFWwindow* getBoundWindow();
		~AQ_OpenGL();
	};
}