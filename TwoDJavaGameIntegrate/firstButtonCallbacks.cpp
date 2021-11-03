#include "headers/firstButtonCallbacks.hpp"
#include <headers/AQ_CompBoxButton2D.hpp>
#include <headers/AQ_GlobalCtrl.hpp>
#include "headers/glConfigCallbacks.h"

namespace firstButton {
	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		//AQ_CompBoxButton2D* button2D = gameObjectCtrl->getComponent<AQ_CompBoxButton2D>(gameObjectThis, "FirstButton2");

	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}

	void processInputs(GLFWwindow* window, AQ_GameObject* gameObjectThis, AQ_GlobalCtrl::TimeCtrl* timeCtrl,
		unsigned int* keys, unsigned int* actions) {
		AQ_CompBoxButton2D* firstButton = gameObjectThis->getGameObjectCtrl()->getComponent<AQ_CompBoxButton2D>(gameObjectThis, "FirstButton2D");
		if (glfwGetKey(window, keys[0]) == actions[0]) {
			std::cout << "Key pressed\n";
			firstButton->clickCheck(MousePosCallback::getXPos(), MousePosCallback::getYPos(), false);
		}
	}
}