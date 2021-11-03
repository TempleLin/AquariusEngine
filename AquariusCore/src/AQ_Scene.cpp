#include "headers/AQ_Scene.hpp"
#include "headers/AQ_Component.hpp"

namespace aquarius_engine {
	AQ_Scene::GameObjects::GameObjects(AQ_Scene* sceneRef) {
		components = new AQ_Scene::GameObjects::Components();
		this->sceneRef = sceneRef;
	}

	AQ_Scene* AQ_Scene::GameObjects::getScene() {
		return sceneRef;
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

	AQ_Scene::AQ_Scene(GLFWwindow* currentWindow) : currentWindow(currentWindow){
		gameObjects = new AQ_Scene::GameObjects(this);
		globals = new AQ_Scene::Globals();
	}

	AQ_Scene::GameObjects* AQ_Scene::getGameObjects() {
		return gameObjects;
	}

	AQ_Scene::Globals* AQ_Scene::getGlobals() {
		return globals;
	}

	GLFWwindow* AQ_Scene::getCurrentWindow() {
		return this->currentWindow;
	}

	AQ_Scene::~AQ_Scene() {
		delete gameObjects;
		delete globals;
	}
}