#pragma once
#include "AQ_CompModel.hpp"
#include "AQ_CompCamera.hpp"
#include "AQ_Lights.hpp"

#include <unordered_map>
#include <vector>
#include <any>
#include <iostream>

namespace aquarius_engine {
	class AQ_Component;

	class AQ_Database {
		friend class AQ_GameObject;
		friend class AQ_GlobalCtrl;
		friend class LightsCtrl;
		friend class AQ_GameObjectCtrl;
	public:
		class Components {
			friend class AQ_GameObject;
			friend class AQ_GameObjectCtrl;
		private:
			// @currentKey will keep += 1 and never repeat for every keys throughout the map of components.
			unsigned int currentKeyIndex;
			// @Create the map in heap allocation to prevent getting destructed before any other GameObject do.
			std::unordered_map<unsigned int, std::any> allComponents;

			// @Gets called from GameObjectCtrl when adding component to GameObject.
			template<typename T>
			void addComponent(T& component, unsigned int& returnKey) {
				allComponents.insert(std::pair<unsigned int, std::any>(currentKeyIndex, component));
				returnKey = currentKeyIndex;
				currentKeyIndex++;
			}
		};

		class GlobalLights {
			friend class AQ_GlobalCtrl;
			friend class LightsCtrl;
		private:
			std::vector<AQ_DirLight> directionalLights;
			std::vector<AQ_PointLight> pointLights;
			std::vector<AQ_SpotLight> spotLights;
		};
	};
}