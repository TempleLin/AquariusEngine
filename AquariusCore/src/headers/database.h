#pragma once
#include <map>
#include "model.h"
#include <iostream>
class AQ_Component;

class AQ_DataBase {
	friend class AQ_GameObject;
private:
	// @currentKey will keep += 1 and never repeat for every keys throughout database
	static inline unsigned int currentKeyIndex = 1;
	static inline std::map<unsigned int, Model> modelComponents;

	template<typename T>
	static void addComponent(T component, unsigned int& returnKey) {
		static_assert(std::is_base_of<AQ_Component, T>::value, "Must be component type.");
		if (typeid(T) == typeid(Model)) {
			try {
				modelComponents.insert(std::pair<unsigned int, Model>(currentKeyIndex, component));
				returnKey = currentKeyIndex;
				currentKeyIndex++;
			}
			catch (...) {
				std::cout << "ERROR: ADDING COMPONENT -- MODEL FAILED" << "\n";
			}
		} else {
			std::cout << "ERROR: CANNOT ADD THIS COMPONENT -- MODEL" << "\n";
		}
	}

	template<typename T>
	static T& getComponent(unsigned int key) {
		static_assert(std::is_base_of<AQ_Component, T>::value, "Must be component type.");
		if (typeid(T) == typeid(Model)) {
			try {
				return modelComponents.find(key)->second;
			}
			catch (...) {
				std::cout << "ERROR: GETTING COMPONENT -- MODEL FAILED" << "\n";
			}
		} else {
			std::cout << "ERROR: COMPONENT DOESN'T EXIST" << "\n";
		}
	}
};