#include "headers/backgroundCallbacks.h"
#include "headers/PassingValues.hpp"
#include <headers/AQ_CompSimpleBox2D.hpp>

namespace background_callbacks {
	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		AQ_CompSimpleBox2D* background2D = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "Background2D");
		int returnTexIndex{}, returnTexIndex1{};
		background2D->addDiffuseTexture("assets/background.png", "Background2DTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
			true, &returnTexIndex);
		background2D->transformScale(glm::vec3(2.f, 2.f, 1.f));
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::MAINHALL) {
			static AQ_CompSimpleBox2D* background2D = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "Background2D");
			background2D->draw();
		}
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}
}