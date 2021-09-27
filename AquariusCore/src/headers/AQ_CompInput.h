#pragma once
#include <List>
#include <map>

enum class AQ_EInputControllerTypes {
	KEYBOARD = -1000000,
	MOUSE = -2000000,
	JOYSTICK = -3000000,
	CLIPBOARD = -4000000,
	PATHDROP = -5000000
};

// TODO: Add influence ability to selected component target.
class AQ_CompInput {
private:
	std::map<AQ_EInputControllerTypes, std::map<int, int>> controllersToUseWithInputs;
public:
	AQ_CompInput(std::map<AQ_EInputControllerTypes, std::map<int, int>> controllersToUseWithInputs)
		: controllersToUseWithInputs(controllersToUseWithInputs) {
	}
	void addOrChangeInputKey(AQ_EInputControllerTypes controllerType, std::pair<int, int> inputKey);
	void removeInputKey(AQ_EInputControllerTypes controllerType, std::pair<int, int> inputKey);
	void removeWholeController(AQ_EInputControllerTypes controllerType);
};