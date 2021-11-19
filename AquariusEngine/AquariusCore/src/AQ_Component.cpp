#include "headers/AQ_Component.hpp"
#include "headers/AQ_GameObject.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

namespace aquarius_engine {
	AQ_GameObject* AQ_Component::getGameObject() {
		return gameObjectThis;
	}

	std::string AQ_Component::getName() {
		return this->name;
	}

	glm::mat4 AQ_Component::getTransform() {
		/*
		* @Temporary move offset to gameObject origin (So that the component's rotation is same as the gameObject), 
		*  then translate back (Now the translation is relative to the rotation.),
		*  then rotate the component back to its original rotation.
		*/
		glm::mat4 tempTransformOffset = *(this->gameObjectTrans);

		glm::vec3 scale;
		glm::quat rotationQuat; //Quaternion.
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;

		glm::decompose(transformOffset, scale, rotationQuat, translation, skew, perspective);
		glm::mat4 rotation = glm::toMat4(rotationQuat);

		tempTransformOffset = glm::translate(tempTransformOffset, translation);
		tempTransformOffset = glm::scale(tempTransformOffset, scale);
		tempTransformOffset = tempTransformOffset * rotation;
		return tempTransformOffset;
	}
	void AQ_Component::transformReset() {
		transformOffset = glm::mat4(1.f);
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
	void AQ_Component::setTransform(glm::mat4 transform) {
		this->transformOffset = transform;
	}
}