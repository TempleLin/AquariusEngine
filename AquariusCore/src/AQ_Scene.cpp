#include "headers/AQ_Scene.hpp"
#include "headers/AQ_Component.hpp"

namespace aquarius_engine {
	AQ_Scene::GameObjects::GameObjects() {
		components = new AQ_Scene::GameObjects::Components();
	}

	AQ_Scene::GameObjects::~GameObjects() {
		for (auto pair : allGameObjects) {
			if (pair.second) {
				delete pair.second;
			}
		}
		delete components;
	}

	AQ_Scene::GameObjects::Components::~Components() {
		for (auto pair : allComponents) {
			if (pair.second) {
				delete static_cast<AQ_Component*>(pair.second);
			}
		}
	}

	AQ_Scene::AQ_Scene() {
		gameObjects = new AQ_Scene::GameObjects();
		globals = new AQ_Scene::Globals();
	}

	AQ_Scene::GameObjects* AQ_Scene::getGameObjects() {
		return gameObjects;
	}

	AQ_Scene::Globals* AQ_Scene::getGlobals() {
		return globals;
	}

	AQ_Scene::~AQ_Scene() {
		delete gameObjects;
		delete globals;
	}
}