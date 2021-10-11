#pragma once
#include "AQ_Database.h"
#include <glm/glm.hpp>

class AQ_GlobalCtrl {
public:
	class LightsCtrl {
	private:
		AQ_Database::GlobalLights* databaseGlobalLights;
	public:
		LightsCtrl(AQ_Database::GlobalLights& databaseGlobalLights);
		void addDirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity);
		void addPointLight(glm::vec3 position, float radius, float intensity);
		void addSpotLight(glm::vec3 position, glm::vec3 direction, float cutoffAngle, float intensity);
	};
};