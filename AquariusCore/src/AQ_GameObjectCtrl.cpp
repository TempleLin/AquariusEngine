#include "headers/AQ_GameObjectCtrl.hpp"
#include "headers/AQ_Component.hpp"
#include <stdexcept>
#include <any>

namespace aquarius_engine {
	AQ_GameObjectCtrl::AQ_GameObjectCtrl(AQ_Database::Components* databaseComponent, AQ_Database::GameObjects* databaseGameObjects) {
		this->databaseComponent = databaseComponent;
		this->databaseGameObjects = databaseGameObjects;
	}

	AQ_GameObject* AQ_GameObjectCtrl::createGameObject(std::string name) {
		if (!(databaseGameObjects->allGameObjects.count(name))) {
			AQ_GameObject* toStashGameObject = new AQ_GameObject(this, name);
			databaseGameObjects->createGameObject(toStashGameObject, name);
			return toStashGameObject;
		}
		else
			std::cout << "ERROR: GAMEOBJECT TO CREATE: " << name << " ALREADY EXISTS" << "\n";
	}

	void AQ_GameObjectCtrl::deleteGameObject(std::string name) {
		if (databaseGameObjects->allGameObjects.count(name)) {
			try {
				delete databaseGameObjects->allGameObjects.at(name);
			} catch (std::out_of_range& e) {
				std::cout << "ERROR: GAMEOBJECT TO DELETE NOT FOUND: " << name << " ERROR DESCRIPTION: " << e.what() << "\n";
			}
		} else {
			std::cout << "UNKNOWN ERROR: GAMEOBJECT TO DELETE NOT FOUND: " << name << "\n";
		}
	}

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

	void AQ_GameObjectCtrl::removeAllCompsOfGameObject(AQ_GameObject* gameObject) {
		try {
			const auto& allComponentsKeysMapRef = gameObject->componentsKeys;
			for (auto const& i : allComponentsKeysMapRef) {
				for (auto const& j : i.second) {
					try {
						delete static_cast<AQ_Component*>(databaseComponent->allComponents.at(j.second));
						databaseComponent->allComponents.erase(j.second);
					} catch (std::out_of_range& e) {
						std::cout << "ERROR: CANNOT REMOVE ALL COMPONENTS OF GAMEOBJECT ERROR DESCRIPTION: " << e.what() << "\n";
					} catch (...) {
						std::cout << "UNKNOWN ERROR: CANNOT REMOVE ALL COMPONENTS OF GAMEOBJECT\n";
					}
				}
			}
		} catch (...) {
			std::cout << "ERROR: UNKNOWN ERROR IN FAILING TO REMOVE ALL COMPONENTS OF GAMEOBJECT" << "\n";
		}
	}
}