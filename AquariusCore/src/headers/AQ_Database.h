#pragma once
#include "AQ_Model.h"
#include "AQ_CompCamera.h"
#include "AQ_Lights.h"
#include "AQ_ModelCtrl.h"

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
	friend class AQ_ModelCtrl;
	friend class AQ_CompModel;
private:
	class Components {
		friend class AQ_GameObject;
		friend class AQ_GameObjectCtrl;
	private:
		// @currentKey will keep += 1 and never repeat for every keys throughout the map of components.
		static unsigned int currentKeyIndex;
		// @Create the map in heap allocation to prevent getting destructed before any other GameObject do.
		inline static std::unordered_map<unsigned int, std::any>& allComponents 
			= *(new std::unordered_map<unsigned int, std::any>);

		// @Gets called from GameObjectCtrl when adding component to GameObject.
		template<typename T>
		static void addComponent(T& component, unsigned int& returnKey) {
			allComponents.insert(std::pair<unsigned int, std::any>(currentKeyIndex, component));
			returnKey = currentKeyIndex;
			currentKeyIndex++;
		}
	};

	class GlobalLights {
		friend class AQ_GlobalCtrl;
		friend class LightsCtrl;
	private:
		static std::vector<AQ_DirLight> directionalLights;
		static std::vector<AQ_PointLight> pointLights;
		static std::vector<AQ_SpotLight> spotLights;
	};

	class Models {
		friend class AQ_ModelCtrl;
		friend class AQ_CompModel;
	private:
		static std::vector<AQ_Model> allModels;
	};
};