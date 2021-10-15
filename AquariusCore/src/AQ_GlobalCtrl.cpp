#include "headers/AQ_GlobalCtrl.hpp"
#include "headers/AQ_Database.hpp"
#include "headers/AQ_CompInput.hpp"
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

AQ_GlobalCtrl::InputSystemCtrl::InputSystemCtrl(AQ_GlobalCtrl::TimeCtrl& timeCtrlReference) {
	this->timeCtrlReference = &timeCtrlReference;
}

void AQ_GlobalCtrl::InputSystemCtrl::processInputs() {
	for (int i = 0; i < allInputComps.size(); i++) {
		try {
			auto& currentInputComp = allInputComps.at(i);
			if (allInputComps.at(i)) {
				auto inputToProcess = currentInputComp->processInputs;
				(*inputToProcess)(currentInputComp->belongedWindow, currentInputComp->gameObjectsToAffect, timeCtrlReference);
			}
		} catch (const std::bad_function_call& e) {
			std::cout << "ERROR: Input function calling failed--" << e.what() << "\n";
		} catch (...) {
			std::cout << "ERROR: UNKNOWN ERROR IN INPUT FUNCTION CALL" << "\n";
		}
	}
}

void AQ_GlobalCtrl::TimeCtrl::updateTime() {
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	// Count seconds using deltaTime
	iSecondsInGame += deltaTime;
}

float AQ_GlobalCtrl::TimeCtrl::getDeltaTime() {
	return deltaTime;
}

float AQ_GlobalCtrl::TimeCtrl::getSecondsInGame() {
	return iSecondsInGame;
}