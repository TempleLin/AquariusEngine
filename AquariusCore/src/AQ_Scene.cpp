#include "headers/AQ_Scene.hpp"

namespace aquarius_engine {
	AQ_Scene::GameObjects::GameObjects() {
		components = new AQ_Scene::GameObjects::Components();
	}

	AQ_Scene::GameObjects::~GameObjects() {
		delete components;
	}
}