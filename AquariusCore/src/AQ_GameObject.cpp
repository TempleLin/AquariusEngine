#include "headers/AQ_GameObject.hpp"
#include "headers/AQ_GameObjectCtrl.hpp"

namespace aquarius_engine {
	AQ_GameObject::AQ_GameObject(AQ_GameObjectCtrl* gameObjectCtrl, std::string name) : startCallback(nullptr), 
		updateCallback(nullptr), gameObjectCtrlPtr(gameObjectCtrl), name(name), componentsCallbackPass(nullptr) {

	}

	void AQ_GameObject::setStartCallback(void (*startCallback)(AQ_GameObjectCtrl* gameObjectCtrl,
		AQ_GameObject* gameObjectThis, AQ_Component** components, void* otherRefs)) {
		this->startCallback = startCallback;
	}

	void AQ_GameObject::setUpdateCallback(void (*updateCallback)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis, 
		AQ_Component** components, void* otherRefs)) {
		this->updateCallback = updateCallback;
	}

	AQ_GameObject::~AQ_GameObject() {
		if (componentsCallbackPass)
			delete[] componentsCallbackPass;
		gameObjectCtrlPtr->removeAllCompsOfGameObject(this);
	}
}