#include "headers/firstButtonCallbacks.hpp"
#include <headers/AQ_CompBoxButton2D.hpp>

namespace firstButton {
	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		AQ_CompBoxButton2D* button2D = gameObjectCtrl->getComponent<AQ_CompBoxButton2D>(gameObjectThis, "FirstButton2");

	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}
}