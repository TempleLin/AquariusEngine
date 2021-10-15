#pragma once
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "AQ_GameObject.hpp"
#include "AQ_GlobalCtrl.hpp"
#include "AQ_Component.hpp"

class AQ_CompInput : public AQ_Component{
	friend class AQ_GlobalCtrl;
	friend class InputSystemCtrl;
private:
	AQ_GameObject** gameObjectsToAffect;
	unsigned int gameObjectsCount;
	AQ_GlobalCtrl::InputSystemCtrl* pointerToInputSystemCtrl;
	GLFWwindow* belongedWindow;
	std::function<void(GLFWwindow* window, AQ_GameObject**, AQ_GlobalCtrl::TimeCtrl* timeCtrl)>* processInputs;
public:
	AQ_CompInput(GLFWwindow* belongedWindow, AQ_GameObject** gameObjectsToAffect, unsigned int gameObjectsCount,
		std::function<void(GLFWwindow* window, AQ_GameObject**, AQ_GlobalCtrl::TimeCtrl* timeCtrl)>* processInputs,
		 AQ_GlobalCtrl::InputSystemCtrl& inputSystemCtrl);
	~AQ_CompInput();
};