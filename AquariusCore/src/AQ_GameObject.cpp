#include "headers/AQ_GameObject.hpp"
#include "headers/AQ_GameObjectCtrl.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace aquarius_engine {
	AQ_GameObject::AQ_GameObject(AQ_GameObjectCtrl* gameObjectCtrl, std::string name) : startCallback(nullptr), 
		updateCallback(nullptr), stopCallback(nullptr), gameObjectCtrlPtr(gameObjectCtrl), name(name), componentsRefs(nullptr), otherRefs(nullptr),
	transform(glm::mat4(1.f)) {

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

	glm::mat4 AQ_GameObject::getTransform() {
		return this->transform;
	}
	void AQ_GameObject::transformTranslate(glm::vec3 translateVector) {
		this->transform = glm::translate(this->transform, translateVector);
	}
	void AQ_GameObject::transformRotate(glm::vec3 rotateVector, float angle) {
		this->transform = glm::rotate(this->transform, glm::radians(angle), rotateVector);
	}
	void AQ_GameObject::transformScale(glm::vec3 scaleVector) {
		this->transform = glm::scale(this->transform, scaleVector);
	}

	std::string AQ_GameObject::getName() {
		return this->name;
	}

	AQ_GameObject::~AQ_GameObject() {
		gameObjectCtrlPtr->removeAllCompsOfGameObject(this);
	}
}