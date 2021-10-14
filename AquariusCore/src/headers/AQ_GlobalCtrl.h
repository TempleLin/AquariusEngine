#pragma once
#include "AQ_Database.h"
#include <vector>
#include <glm/glm.hpp>

class AQ_CompInput;

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
	class InputSystemCtrl {
		friend class AQ_CompInput;
	private:
		std::vector<AQ_CompInput*> allInputComps;
		void addInputComp(AQ_CompInput& compInput);
	public:
		void processInputs();
	};
};