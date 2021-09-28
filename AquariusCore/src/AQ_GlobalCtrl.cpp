#include "headers/AQ_GlobalCtrl.h"
#include "headers/AQ_Database.h"

void AQ_GlobalCtrl::LightsCtrl::addDirectionalLight
	(glm::vec3 direction, glm::vec3 color, float intensity) {
	AQ_Database::GlobalLights::directionalLights.push_back(AQ_DirLight(direction, color, intensity));
}

void AQ_GlobalCtrl::LightsCtrl::addPointLight
	(glm::vec3 position, float radius, float intensity) {
	AQ_Database::GlobalLights::pointLights.push_back(AQ_PointLight(position, radius, intensity));
}

void AQ_GlobalCtrl::LightsCtrl::addSpotLight
	(glm::vec3 position, glm::vec3 direction, float cutoffAngle, float intensity) {
	AQ_Database::GlobalLights::spotLights.push_back(AQ_SpotLight(position, direction, cutoffAngle, intensity));
}