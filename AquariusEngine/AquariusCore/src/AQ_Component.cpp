#include "headers/AQ_Component.hpp"
#include "headers/AQ_GameObject.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

namespace aquarius_engine {
	AQ_GameObject* AQ_Component::getGameObject() {
		return gameObjectThis;
	}

	std::string AQ_Component::getName() {
		return this->name;
	}

	glm::mat4 AQ_Component::getTransform() {
		/*
		* @Translate back to the gameObject's position origin first, then rotate, then translate back. Results in correct relative position
		*  when the component is not at gameObject's position and the gameObject rotates.
		*/
		glm::vec3 offsetFromOrigin = glm::vec3(transformOffset[0][3], transformOffset[1][3],
			transformOffset[2][3]);
		transformOffset = glm::translate(transformOffset, -offsetFromOrigin);

		glm::vec3 scale;
		glm::quat rotationQuat; //Quaternion.
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(*(this->gameObjectTrans), scale, rotationQuat, translation, skew, perspective);
		glm::mat4 rotation = glm::toMat4(rotationQuat);

		transformOffset =  rotation * transformOffset;
		transformOffset = glm::translate(transformOffset, offsetFromOrigin);
		return transformOffset;
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
}