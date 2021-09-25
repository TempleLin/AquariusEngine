#pragma once
#include <map>
#include <vector>
#include <type_traits>

#include "AQ_Database.h"
#include "AQ_Component.h"
class AQ_CompModel;

class AQ_GameObject {
private:
	std::vector<AQ_Component> components;
public:
	template<typename T>
	inline void addComponent(T component) {
		static_assert(std::is_base_of<AQ_Component, T>::value, "Must be component type.");
		try {
			AQ_DataBase::Components::addComponent<T>(component, component.dataBaseAcessKey);
			components.push_back(component);
		}
		catch (...) {
			std::cout << "ERROR: CAN'T ADD COMPONENT TO DATABASE FROM GAMEOBJECT" << "\n";
		}
	}
	template<typename T>
	inline T& getComponent(unsigned int index) {
		static_assert(std::is_base_of<AQ_Component, T>::value, "Must be component type.");
		for (auto i : components) {
			if (i.type == typeid(T)) {
				if (index) {
					index -= 1;
				} else {
					return AQ_DataBase::Components::getComponent<T>(i.dataBaseAcessKey);
				}
			}
		}
		throw - 1;
	}
};