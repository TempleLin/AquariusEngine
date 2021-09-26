#include "headers/AQ_GameObjectCtrl.h"
#include <exception>

void AQ_GameObjectCtrl::addCameraComponent(AQ_GameObject& gameObject, AQ_CompCamera camera) {
	AQ_Database::Components::addCameraComponent(camera, camera.databaseAccessKey);
	gameObject.cameraComponentsKeys.push_back(camera.databaseAccessKey);
}

void AQ_GameObjectCtrl::addModelComponent(AQ_GameObject& gameObject, AQ_CompModel model) {
	AQ_Database::Components::addModelComponent(model, model.databaseAccessKey);
	gameObject.modelComponentsKeys.push_back(model.databaseAccessKey);
}

AQ_CompCamera& AQ_GameObjectCtrl::getCameraComponent(AQ_GameObject& gameObject, unsigned int index) {
	try {
		return AQ_Database::Components::getCameraComponent(gameObject.cameraComponentsKeys.at(index));
	} catch (std::out_of_range& e) {
		std::cout << "Failed to get component:" << typeid(AQ_CompCamera).name() << "--" << e.what() << "\n";
	}
}

AQ_CompModel& AQ_GameObjectCtrl::getModelComponent(AQ_GameObject& gameObject, unsigned int index) {
	try {
		return AQ_Database::Components::getModelComponent(gameObject.modelComponentsKeys.at(index));
	} catch (std::out_of_range& e) {
		std::cout << "Failed to get component:" << typeid(AQ_CompModel).name() << "--" << e.what() << "\n";
	}
}