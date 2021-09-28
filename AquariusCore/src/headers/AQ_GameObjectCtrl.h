#pragma once
#include "AQ_GameObject.h"
#include "AQ_CompModel.h"
#include "AQ_CompCamera.h"
#include "AQ_Database.h"
#include "AQ_Component.h"
#include <string>
#include <iostream>
#include <type_traits>
#include <utility>
#include <any>

class AQ_GameObjectCtrl {
public:
	template <typename T>
	static void addComponent(AQ_GameObject& gameObject, T component, std::string name) {
		if constexpr (std::is_base_of<AQ_Component, T>::value) {
			try {
				component.name = name;
				AQ_Database::Components::addComponent(component, component.databaseAccessKey);
				const auto& componentsKeysVecRef = gameObject.componentsKeys[typeid(T)];
				for (int i = 0; i < componentsKeysVecRef.size(); i++) {
					if (componentsKeysVecRef.at(i).first == name) {
						throw std::string("ERROR: GAMEOBJECT'S SAME COMPONENT TYPE ALREADY HAS ONE WITH THE NAME");
					}
				}
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
				std::string stringHolder = "";
				int i = 0;
				for (; i < componentsKeysVecRef.size(); i++) {
					if (componentsKeysVecRef.at(i).first == name) {
						stringHolder = name;
						break;
					}
				}
				if (stringHolder == "") {
					throw std::out_of_range("COMPONENT WITH SPECIFIED NAME DOESN'T EXIST IN SPECIFIED COMPONENT TYPE");
				} else {
					return std::any_cast<T&>(AQ_Database::Components::allComponents.at(componentsKeysVecRef.at(i).second));
				}
			} catch (std::out_of_range& e) {
				std::cout << "FAILED TO GET COMPONENT FROM GAMEOBJECT CTRL" << e.what() << "\n";
			} catch (...) {
				std::cout << "ERROR: UNKNOW ERROR FROM GETTING COMPONENT IN AQ_GAMEOBJECTCTRL" << "\n";
			}
		}
	}
};

#define AQ_AddComponent AQ_GameObjectCtrl::addComponent
#define AQ_GetComponent AQ_GameObjectCtrl::getComponent