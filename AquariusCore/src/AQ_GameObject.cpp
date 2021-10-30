#include "headers/AQ_GameObject.hpp"
#include "headers/AQ_GameObjectCtrl.hpp"

namespace aquarius_engine {
	AQ_GameObject::AQ_GameObject(AQ_GameObjectCtrl* gameObjectCtrl, std::string name) : startCallback(nullptr), 
		updateCallback(nullptr), stopCallback(nullptr), gameObjectCtrlPtr(gameObjectCtrl), name(name), componentsRefs(nullptr), otherRefs(nullptr) {

	}

	void AQ_GameObject::setStartCallback(void (*startCallback)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis)) {
		this->startCallback = startCallback;
	}

	void AQ_GameObject::setUpdateCallback(void (*updateCallback)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis)) {
		this->updateCallback = updateCallback;
	}

	void AQ_GameObject::setStopCallback(void (*stopCallback)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis)) {
		this->stopCallback = stopCallback;
	}

	void AQ_GameObject::setComponentsRefs(AQ_Component** compsRefs) {
		if (this->componentsRefs)
			delete[] componentsRefs;
		this->componentsRefs = compsRefs;
	}

	void AQ_GameObject::setOtherRefs(void** otherRefs) {
		if (this->otherRefs)
			delete[] this->otherRefs;
		this->otherRefs = otherRefs;
	}

	AQ_Component** AQ_GameObject::getComponentsRefs() {
		return componentsRefs;
	}

	void** AQ_GameObject::getOtherRefs() {
		return otherRefs;
	}

	AQ_GameObject::~AQ_GameObject() {
		gameObjectCtrlPtr->removeAllCompsOfGameObject(this);
	}
}