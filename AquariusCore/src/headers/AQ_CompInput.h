#pragma once
#include <vector>
#include <functional>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "AQ_GameObject.h"
#include "AQ_GlobalCtrl.h"
#include "AQ_Component.h"

class AQ_CompInput : public AQ_Component{
	friend class AQ_GlobalCtrl;
	friend class InputSystemCtrl;
private:
	AQ_GameObject** gameObjectsToAffect;
	AQ_GlobalCtrl::InputSystemCtrl* pointerToInputSystemCtrl;
	GLFWwindow* belongedWindow;
	std::shared_ptr<std::function<void(GLFWwindow* window, AQ_GameObject**)>> processInputs;
public:
	AQ_CompInput(GLFWwindow* belongedWindow, AQ_GameObject** gameObjectsToAffect, 
		std::function<void(GLFWwindow* window, AQ_GameObject**)>* processInputs, AQ_GlobalCtrl::InputSystemCtrl& inputSystemCtrl);
	~AQ_CompInput();
};