#include "headers/backgroundCallbacks.h"
#include "headers/PassingValues.hpp"
#include <headers/AQ_CompSimpleBox2D.hpp>

namespace background_callbacks {
	void backgroundPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::MAINHALL) {
			AQ_CompSimpleBox2D* background2D = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "Background2D");
			int returnTexIndex{}, returnTexIndex1{};
			background2D->addDiffuseTexture("assets/background.png", "Background2DTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
				true, &returnTexIndex);
			background2D->addDiffuseTexture("assets/TreeElf.png", "TreeElfBackground", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
				true, &returnTexIndex1);
			background2D->activateTexture(GL_TEXTURE0);

			background2D->setShaderID(shaders.at(0).ID);
			background2D->setPreDrawCallback(backgroundPreDrawCallback);
		}
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::MAINHALL) {
			static AQ_CompSimpleBox2D* background2D = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "Background2D");
			background2D->draw();
		}
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}

	void backgroundPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
}