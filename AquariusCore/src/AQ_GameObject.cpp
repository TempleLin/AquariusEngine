#include "headers/AQ_GameObject.hpp"
#include "headers/AQ_GameObjectCtrl.hpp"

namespace aquarius_engine {
	AQ_GameObject::AQ_GameObject(AQ_GameObjectCtrl* gameObjectCtrl, std::string name) : startCallback(nullptr), 
		updateCallback(nullptr), stopCallback(nullptr), gameObjectCtrlPtr(gameObjectCtrl), name(name), componentsRefs(nullptr), otherRefs(nullptr) {

	}

	void AQ_GameObject::setCallbackFuncs(void (*start)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis),
		void (*update)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis),
		void (*stop)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis)) {
		this->startCallback = start;
		this->updateCallback = update;
		this->stopCallback = stop;
	}

	AQ_GameObjectCtrl* AQ_GameObject::getGameObjectCtrl() {
		return gameObjectCtrlPtr;
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