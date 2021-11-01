#pragma once
#include "AQ_CompModel.hpp"
#include "AQ_CompCamera.hpp"
#include "AQ_GameObject.hpp"
#include "AQ_Lights.hpp"

#include <unordered_map>
#include <vector>
#include <iostream>

namespace aquarius_engine {
	class AQ_Component;

	class AQ_Scene {
		friend class AQ_GameObject;
		friend class AQ_GlobalCtrl;
		friend class LightsCtrl;
		friend class AQ_GameObjectCtrl;
	private:
		class GameObjects;
		class Globals;
		GameObjects* gameObjects;
		Globals* globals;
	public:
		class GameObjects {
			friend class AQ_GameObjectCtrl;
			friend class AQ_Scene;
		private:
			class Components;
			Components* components;
			std::unordered_map<std::string, AQ_GameObject*> allGameObjects;

			void createGameObject(AQ_GameObject* gameObject, std::string name) {
				allGameObjects.insert(std::pair<std::string, AQ_GameObject*>(name, gameObject));
			}
			GameObjects();
		public:
			~GameObjects();
			class Components {
				friend class AQ_GameObject;
				friend class AQ_GameObjectCtrl;
			private:
				// @currentKey will keep += 1 and never repeat for every keys throughout the map of components.
				unsigned int currentKeyIndex;
				std::unordered_map<unsigned int, void*> allComponents;

				// @Gets called from GameObjectCtrl when adding component to GameObject.
				void addComponent(void* component, unsigned int& returnKey) {
					allComponents.insert(std::pair<unsigned int, void*>(currentKeyIndex, component));
					returnKey = currentKeyIndex;
					currentKeyIndex++;
				}
			};
		};

		class Globals {
			friend class AQ_Scene;
		private:
			Globals() {};
		public:
			//class GlobalLights {
			//	friend class AQ_GlobalCtrl;
			//	friend class LightsCtrl;
			//private:
			//	GlobalLights() {};
			//	std::vector<AQ_DirLight> directionalLights;
			//	std::vector<AQ_PointLight> pointLights;
			//	std::vector<AQ_SpotLight> spotLights;
			//};
		};
	public:
		AQ_Scene();
		~AQ_Scene();
		GameObjects* getGameObjects();
		Globals* getGlobals();
	};
}