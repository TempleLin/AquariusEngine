#include "headers/AQ_CompInput.h"
#include <iostream>
#include <stdexcept>

void AQ_CompInput::addOrChangeInputKey(AQ_EInputControllerTypes controllerType, std::pair<int, int> inputKey) {
	controllersToUseWithInputs[controllerType][inputKey.first] = inputKey.second;
}

void AQ_CompInput::removeInputKey(AQ_EInputControllerTypes controllerType, std::pair<int, int> inputKey) {
	try {
		controllersToUseWithInputs[controllerType].at(inputKey.first);
		controllersToUseWithInputs[controllerType].erase(inputKey.first);
	} catch (std::out_of_range& e) {
		std::cout << "ERROR: INPUT KEY DOESN'T EXIST, CANNOT REMOVE--" << e.what() << "\n";
	}
}

void AQ_CompInput::clearControllerKeys(AQ_EInputControllerTypes controllerType) {
	try {
		controllersToUseWithInputs.at(controllerType).clear();
	} catch (std::out_of_range& e) {
		std::cout << "ERROR: CONTROLLER DOESN'T EXIST, CANNOT REMOVE--" << e.what() << "\n";
	}
}