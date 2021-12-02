#include "headers/mainhallCallbacks.h"
#include "headers/PassingValues.hpp"
#include <headers/AQ_CompSimpleBox2D.hpp>

namespace mainhall {
	AQ_CompSimpleBox2D* mainhall2D;
	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		mainhall2D = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "Mainhall2D");
		int returnTexIndex{}, returnTexIndex1{};
		mainhall2D->addDiffuseTexture("assets/background.png", "Mainhall2DTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
			true, &returnTexIndex);
		mainhall2D->transformScale(glm::vec3(2.f, 2.f, 1.f));
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::MAINHALL) {
			mainhall2D = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "Mainhall2D");
			mainhall2D->draw();
		}
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}
}