#pragma once
#include <glm/glm.hpp>

namespace aquarius_engine {
	class AQ_Transform {
	public:
		virtual glm::mat4 getTransform() {}
		virtual void transformRotate(glm::vec3 rotateVector, float angle) {}
		virtual void transformTranslate(glm::vec3 translateVector) {}
		virtual void transformScale(glm::vec3 scaleVector) {}
	};
}