#pragma once
#include "AQ_GameObject.h"
#include "AQ_CompModel.h"
#include "AQ_CompCamera.h"
#include "AQ_Database.h"
#include "AQ_Component.h"
#include <iostream>
#include <type_traits>
#include <any>

class AQ_GameObjectCtrl {
public:
	template <typename T>
	static void addComponent(AQ_GameObject& gameObject, T component) {
		if constexpr (std::is_base_of<AQ_Component, T>::value) {
			AQ_Database::Components::addComponent(component, component.databaseAccessKey);
			gameObject.componentsKeys[typeid(T)].push_back(component.databaseAccessKey);
		}
	}

	template <typename T>
	static T& getComponent(AQ_GameObject& gameObject, unsigned int index) {
		if constexpr (std::is_base_of<AQ_Component, T>::value) {
			try {
				return std::any_cast<T&>(AQ_Database::Components::allComponents.at(gameObject.componentsKeys[typeid(T)].at(index)));
			} catch (std::out_of_range& e) {
				std::cout << "FAILED TO GET COMPONENT FROM GAMEOBJECT CTRL" << "\n";
			}
		}
	}
};

#define AQ_AddComponent AQ_GameObjectCtrl::addComponent
#define AQ_GetComponent AQ_GameObjectCtrl::getComponent