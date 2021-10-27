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
		class WindowNamePair {
		public:
			GLFWwindow* window;
			std::string name;
			WindowNamePair(GLFWwindow* window, std::string name);
			~WindowNamePair();
		};
		class Settings {
		public:
			AQ_OpenGL* aq_OpenGL;

			Settings(AQ_OpenGL* openGL);

			Settings& ver_Profile(unsigned int major, unsigned int minor, unsigned int PROFILE);

			Settings& createWindow(unsigned int width, unsigned int height, const char* windowName,
				GLFWmonitor* monitor, GLFWwindow* share, bool bindWindow);

			Settings& setCurrentThreadWindow(GLFWwindow* window);

			void initializeGLAD();
		};
		Settings* settings;
		std::vector<WindowNamePair*> windows;
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