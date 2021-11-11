#pragma once
#include <glm/glm.hpp>

namespace aquarius_engine {
	class AQ_Transform {
	public:
		virtual void transformReset() {}
		virtual glm::mat4 getTransform() { return glm::mat4(1.f); }
		virtual void transformRotate(glm::vec3 rotateVector, float angle) {}
		virtual void transformTranslate(glm::vec3 translateVector) {}
		virtual void transformScale(glm::vec3 scaleVector) {}
	};
}