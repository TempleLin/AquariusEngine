#include "headers/AQ_GlobalCtrl.h"
#include "headers/AQ_Database.h"
#include "headers/AQ_CompInput.h"
#include <iostream>

AQ_GlobalCtrl::LightsCtrl::LightsCtrl(AQ_Database::GlobalLights& databaseGlobalLights) {
	this->databaseGlobalLights = &databaseGlobalLights;
}

void AQ_GlobalCtrl::LightsCtrl::addDirectionalLight
	(glm::vec3 direction, glm::vec3 color, float intensity) {
	databaseGlobalLights->directionalLights.push_back(AQ_DirLight(direction, color, intensity));
}

void AQ_GlobalCtrl::LightsCtrl::addPointLight
	(glm::vec3 position, float radius, float intensity) {
	databaseGlobalLights->pointLights.push_back(AQ_PointLight(position, radius, intensity));
}

void AQ_GlobalCtrl::LightsCtrl::addSpotLight
	(glm::vec3 position, glm::vec3 direction, float cutoffAngle, float intensity) {
	databaseGlobalLights->spotLights.push_back(AQ_SpotLight(position, direction, cutoffAngle, intensity));
}

void AQ_GlobalCtrl::InputSystemCtrl::addInputComp(AQ_CompInput& compInput) {
	allInputComps.push_back(&compInput);
}

void AQ_GlobalCtrl::InputSystemCtrl::processInputs() {
	for (int i = 0; i < allInputComps.size(); i++) {
		try {
			auto inputToProcess = (allInputComps.at(i))->processInputs;
			(*inputToProcess)();
			std::cout << "Processing inputs" << std::endl;
		} catch (const std::bad_function_call& e) {
			std::cout << "ERROR: Input function calling failed--" << e.what() << "\n";
		} catch (...) {
			std::cout << "ERROR: UNKNOWN ERROR IN INPUT FUNCTION CALL" << "\n";
		}
	}
}