#pragma once
#include <typeinfo>
#include <string>
#include <glm/glm.hpp>
#include "AQ_Transform.hpp"

namespace aquarius_engine {

	class AQ_GameObject;

	enum class AQ_EComponents {
		CAMERA, MODEL
	};

	class AQ_Component : public AQ_Transform{
		friend class AQ_GameObject;
		friend class AQ_GameObjectCtrl;
	protected:
		AQ_GameObject* gameObjectThis;
		glm::mat4* gameObjectTrans;
		glm::mat4 transformOffset;
		unsigned int databaseAccessKey;
		std::string name;
	public:
		AQ_GameObject* getGameObject();

		virtual glm::mat4 getTransform();
		virtual void transformRotate(glm::vec3 rotateVector, float angle);
		virtual void transformTranslate(glm::vec3 translateVector);
		virtual void transformScale(glm::vec3 scaleVector);

		virtual ~AQ_Component() {}
	};
}