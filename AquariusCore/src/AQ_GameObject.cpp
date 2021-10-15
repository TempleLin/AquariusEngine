#include "headers/AQ_GameObject.hpp"
#include "headers/AQ_GameObjectCtrl.hpp"

namespace aquarius_engine {
	AQ_GameObject::AQ_GameObject(AQ_GameObjectCtrl& gameObjectCtrl) {
		this->gameObjectCtrlPtr = &gameObjectCtrl;
	}

	AQ_GameObject::~AQ_GameObject() {
		gameObjectCtrlPtr->removeAllCompsOfGameObject(*this);
	}
}