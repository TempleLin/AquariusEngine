#pragma once
#include <glm/glm.hpp>

class AQ_GlobalCtrl {
public:
	static class LightsCtrl {
	public:
		static void addDirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity);
		static void addPointLight(glm::vec3 position, float radius, float intensity);
		static void addSpotLight(glm::vec3 position, glm::vec3 direction, float cutoffAngle, float intensity);
	};
};