#include "headers/AQ_Component.hpp"
#include "headers/AQ_GameObject.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace aquarius_engine {
	AQ_GameObject* AQ_Component::getGameObject() {
		return gameObjectThis;
	}

	std::string AQ_Component::getName() {
		return this->name;
	}

	glm::mat4 AQ_Component::getTransform() {
		return this->transformOffset * *(this->gameObjectTrans);
	}
	void AQ_Component::transformRotate(glm::vec3 rotateVector, float angle) {
		this->transformOffset = glm::rotate(this->transformOffset, glm::radians(angle), rotateVector);
	}
	void AQ_Component::transformTranslate(glm::vec3 translateVector) {
		this->transformOffset = glm::translate(this->transformOffset, translateVector);
	}
	void AQ_Component::transformScale(glm::vec3 scaleVector) {
		this->transformOffset = glm::scale(this->transformOffset, scaleVector);
	}
}