#include "headers/shopCallbacks.h"
#include "headers/PassingValues.hpp"
#include <headers/AQ_GameObjectCtrl.hpp>
#include <headers/AQ_GameObject.hpp>
#include <headers/AQ_CompSimpleBox2D.hpp>

namespace shop {
	using namespace aquarius_engine;
	void backgroundPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);
	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		AQ_CompSimpleBox2D* shopBackground = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "ShopBackground");
		int returnTextIndex{};
		shopBackground->addDiffuseTexture("assets/ShopBackground.png", "ShopBackgroundImageText", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
			true, &returnTextIndex);
		shopBackground->activateTexture(GL_TEXTURE0);
		shopBackground->setShaderID(shaders.at(0).ID);
		shopBackground->setPreDrawCallback(backgroundPreDrawCallback);
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::SHOP) {
			static AQ_CompSimpleBox2D* shopBackground = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "ShopBackground");
			shopBackground->draw();
		}
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::SHOP) {

		}
	}
	void backgroundPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
}