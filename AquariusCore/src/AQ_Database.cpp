#include "headers/AQ_Database.h"

unsigned int AQ_Database::Components::currentKeyIndex = 1;
std::unordered_map<unsigned int, AQ_CompModel> AQ_Database::Components::modelComponents;
std::unordered_map<unsigned int, AQ_CompCamera> AQ_Database::Components::cameraComponents;

void AQ_Database::Components::addCameraComponent(AQ_CompCamera& component, unsigned int& returnKey) {
	cameraComponents.insert(std::pair<unsigned int, AQ_CompCamera>(currentKeyIndex, component));
	returnKey = currentKeyIndex;
	currentKeyIndex++;
}

void AQ_Database::Components::addModelComponent(AQ_CompModel& component, unsigned int& returnKey) {
	modelComponents.insert(std::pair<unsigned int, AQ_CompModel>(currentKeyIndex, component));
	returnKey = currentKeyIndex;
	currentKeyIndex++;
}


std::vector<AQ_DirLight> AQ_Database::GlobalLights::directionalLights;
std::vector<AQ_PointLight> AQ_Database::GlobalLights::pointLights;
std::vector<AQ_SpotLight> AQ_Database::GlobalLights::spotLights;