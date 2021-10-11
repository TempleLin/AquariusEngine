#pragma once
#include "AQ_GameObject.h"
#include "AQ_Database.h"
#include "AQ_Component.h"
#include <string>
#include <iostream>
#include <type_traits>
#include <utility>
#include <any>

/*
* @Reminder:
*	1.A gameobject can have components with same name only when they each are different types.
*/

class AQ_GameObjectCtrl {
	friend class AQ_GameObject;
private:
	static unsigned int getComponentIndex(const std::vector<std::pair<std::string, unsigned int>>& compVector,
		std::string& nameOfComponent);
public:
	template <typename T>
	static void addComponent(AQ_GameObject& gameObject, T component, std::string name) {
		if constexpr (std::is_base_of<AQ_Component, T>::value) {
			try {
				component.name = name;
				/*
				* @Add the component with to the database and receive its key in database by returning in to
				*  component object's databaseAccessKey.
				*/
				AQ_Database::Components::addComponent(component, component.databaseAccessKey);
				const auto& componentsKeysVecRef = gameObject.componentsKeys[typeid(T)];
				// @Check if the name specified already exists in the gameobject's components.
				for (int i = 0; i < componentsKeysVecRef.size(); i++) {
					if (componentsKeysVecRef.at(i).first == name) {
						throw std::string("ERROR: GAMEOBJECT'S SAME COMPONENT TYPE ALREADY HAS ONE WITH THE NAME");
					}
				}
				// @Save name and access key to database descriptions of the component to the gameobject.
				gameObject.componentsKeys[typeid(T)].push_back(std::pair<std::string, unsigned int>(name, component.databaseAccessKey));
			} catch (std::string& errorMessage){
				std::cout << errorMessage << "\n";
			} catch (std::out_of_range& e) {
				std::cout << "ERROR: CANNOT ADD COMPONENT FROM GAMEOBJECT" << e.what() << "\n";
			} catch (...) {
				std::cout << "ERROR: UNKNOW ERROR IN ADDCOMPONENT FROM AQ_GAMEOBJECTCTRL" << "\n";
			}
			
		}
	}

	template <typename T>
	static T& getComponent(AQ_GameObject& gameObject, std::string name) {
		if constexpr (std::is_base_of<AQ_Component, T>::value) {
			try {
				const auto& componentsKeysVecRef = gameObject.componentsKeys[typeid(T)];
				return std::any_cast<T&>(AQ_Database::Components::allComponents
					.at(componentsKeysVecRef.at(getComponentIndex(componentsKeysVecRef, name)).second));
			} catch (std::out_of_range& e) {
				std::cout << "FAILED TO GET COMPONENT FROM GAMEOBJECT CTRL" << e.what() << "\n";
			} catch (...) {
				std::cout << "ERROR: UNKNOW ERROR FROM GETTING COMPONENT IN AQ_GAMEOBJECTCTRL" << "\n";
			}
		}
	}

	template <typename T>
	static void removeComponent(AQ_GameObject& gameObject, std::string name) {
		if constexpr (std::is_base_of<AQ_Component, T>::value) {
			try {
				const auto& componentsKeysVecRef = gameObject.componentsKeys[typeid(T)];
				AQ_Database::Components::allComponents.erase
					(componentsKeysVecRef.at(getComponentIndex(componentsKeysVecRef, name)).second);
			} catch (std::out_of_range& e) {
				std::cout << "FAILED TO REMOVE COMPONENT FROM GAMEOBJECT CTRL" << e.what() << "\n";
			} catch (...) {
				std::cout << "ERROR: UNKNOW ERROR FROM REMOVING COMPONENT IN AQ_GAMEOBJECTCTRL" << "\n";
			}
		}
	}

	static void removeAllCompsOfGameObject(AQ_GameObject& gameObject);
};

#define AQ_AddComponent AQ_GameObjectCtrl::addComponent
#define AQ_GetComponent AQ_GameObjectCtrl::getComponent
#define AQ_ClearAllComponents AQ_GameObjectCtrl::removeAllCompsOfGameObject