#pragma once
#include "AQ_CompModel.h"
#include "AQ_CompCamera.h"
#include "AQ_Lights.h"

#include <unordered_map>
#include <vector>
#include <any>
#include <iostream>
class AQ_Component;

class AQ_Database {
	friend class AQ_GameObject;
	friend class AQ_GlobalCtrl;
	friend class LightsCtrl;
	friend class AQ_GameObjectCtrl;
private:
	static class Components {
		friend class AQ_GameObject;
		friend class AQ_GameObjectCtrl;
	private:
		// @currentKey will keep += 1 and never repeat for every keys throughout database
		static unsigned int currentKeyIndex;
		static std::unordered_map<unsigned int, std::any> allComponents;

		template<typename T>
		static void addComponent(T& component, unsigned int& returnKey) {
			allComponents.insert(std::pair<unsigned int, std::any>(currentKeyIndex, component));
			returnKey = currentKeyIndex;
			currentKeyIndex++;
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