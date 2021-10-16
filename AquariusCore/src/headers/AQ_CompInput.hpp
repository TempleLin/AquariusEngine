#pragma once
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "AQ_GameObject.hpp"
#include "AQ_GlobalCtrl.hpp"
#include "AQ_Component.hpp"

namespace aquarius_engine {
	class AQ_CompInput : public AQ_Component {
		friend class AQ_GlobalCtrl;
		friend class InputSystemCtrl;
	private:
		GLFWwindow* belongedWindow;
		AQ_GameObject** gameObjectsReference;
		unsigned int* inputKeys;
		unsigned int* inputActions;
		AQ_GlobalCtrl::InputSystemCtrl* pointerToInputSystemCtrl;
		void (*processInputs)(GLFWwindow* window, AQ_GameObject** gameObjects, AQ_GlobalCtrl::TimeCtrl* timeCtrl,
			unsigned int* keys, unsigned int* actions);
	public:
		AQ_CompInput(GLFWwindow* belongedWindow, AQ_GameObject** gameObjectsReference,
			unsigned int* inputKeys, unsigned int* inputActions,
			void (*callbackProcessInputs)(GLFWwindow* window, AQ_GameObject** gameObjects, AQ_GlobalCtrl::TimeCtrl* timeCtrl, 
				unsigned int* keys, unsigned int* actions),
			AQ_GlobalCtrl::InputSystemCtrl& inputSystemCtrl);
		void rebindCallBack(void (*callbackProcessInputs)(GLFWwindow* window, AQ_GameObject** gameObjects, AQ_GlobalCtrl::TimeCtrl* timeCtrl,
			unsigned int* keys, unsigned int* actions));
		void rebindGameObjectsRef(AQ_GameObject** gameObjectsReference);
		void rebindInputKeys(unsigned int* inputKeys);
		void rebindInputActions(unsigned int* inputActions);
		~AQ_CompInput();
	};
}