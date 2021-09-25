#pragma once
#include "AQ_CompModel.h"
#include "AQ_Lights.h"

#include <map>
#include <vector>
#include <iostream>
class AQ_Component;

class AQ_DataBase {
	friend class AQ_GameObject;
	friend class AQ_GlobalCtrl;
	friend class LightsCtrl;
private:
	static class Components {
		friend class AQ_GameObject;
	private:
		// @currentKey will keep += 1 and never repeat for every keys throughout database
		static unsigned int currentKeyIndex;
		static std::map<unsigned int, AQ_CompModel> modelComponents;

		template<typename T>
		static void addComponent(T component, unsigned int& returnKey) {
			static_assert(std::is_base_of<AQ_Component, T>::value, "Must be component type.");
			if (typeid(T) == typeid(AQ_CompModel)) {
				try {
					modelComponents.insert(std::pair<unsigned int, AQ_CompModel>(currentKeyIndex, component));
					returnKey = currentKeyIndex;
					currentKeyIndex++;
				}
				catch (...) {
					std::cout << "ERROR: ADDING COMPONENT -- MODEL FAILED" << "\n";
				}
			}
			else {
				std::cout << "ERROR: CANNOT ADD THIS COMPONENT -- MODEL" << "\n";
			}
		}

		template<typename T>
		static T& getComponent(unsigned int key) {
			static_assert(std::is_base_of<AQ_Component, T>::value, "Must be component type.");
			if (typeid(T) == typeid(AQ_CompModel)) {
				try {
					return modelComponents.find(key)->second;
				}
				catch (...) {
					std::cout << "ERROR: GETTING COMPONENT -- MODEL FAILED" << "\n";
				}
			}
			else {
				std::cout << "ERROR: COMPONENT DOESN'T EXIST" << "\n";
			}
		}
	};

	static class GlobalLights {
		friend class AQ_GlobalCtrl;
		friend class LightsCtrl;
	private:
		static std::vector<AQ_DirLight> directionalLights;
		static std::vector<AQ_PointLight> pointLights;
		static std::vector<AQ_SpotLight> spotLights;
	};
};