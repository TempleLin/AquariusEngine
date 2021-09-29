#include "headers/AQ_GameObjectCtrl.h"
#include <stdexcept>
#include <any>

unsigned int AQ_GameObjectCtrl::getComponentIndex(const std::vector<std::pair<std::string, unsigned int>>& compVector,
	std::string& nameOfComponent) {
	try {
		for (unsigned int i = 0; i < compVector.size(); i++) {
			if (compVector.at(i).first == nameOfComponent) {
				return i;
			}
		}
		throw std::out_of_range("COMPONENT WITH SPECIFIED NAME DOESN'T EXIST IN SPECIFIED COMPONENT TYPE");
	} catch (std::out_of_range& e) {
		std::cout << e.what() << "\n";
	}
}

void AQ_GameObjectCtrl::removeAllCompsOfGameObject(AQ_GameObject& gameObject) {
	try {
		const auto& allComponentsKeysMapRef = gameObject.componentsKeys;
		for (auto const& i : allComponentsKeysMapRef) {
			for (auto const& j : i.second) {
				AQ_Database::Components::allComponents.erase(j.second);
			}
		}
	} catch (...) {
		std::cout << "ERROR: UNKNOWN ERROR IN FAILING TO REMOVE ALL COMPONENTS OF GAMEOBJECT" << "\n";
	}
}