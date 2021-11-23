#include "headers/shopCallbacks.h"
#include "headers/PassingValues.hpp"
#include <headers/AQ_GameObjectCtrl.hpp>
#include <headers/AQ_GameObject.hpp>
#include <headers/AQ_CompSimpleBox2D.hpp>

namespace shop {
	using namespace aquarius_engine;
	void backgroundPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);
	void coinPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		AQ_CompSimpleBox2D* shopBackground = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "ShopBackground");
		AQ_CompSimpleBox2D* coin = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "Coin");

		int returnTextIndex{};
		shopBackground->addDiffuseTexture("assets/ShopBackground.png", "ShopBackgroundImageText", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
			true, &returnTextIndex);
		shopBackground->activateTexture(GL_TEXTURE0);
		shopBackground->setShaderID(shaders.at(0).ID);
		shopBackground->setPreDrawCallback(backgroundPreDrawCallback);

		coin->addDiffuseTexture("assets/Coin.png", "Coin2DTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &returnTextIndex);
		coin->activateTexture(GL_TEXTURE0);
		coin->setShaderID(shaders.at(0).ID);
		coin->setPreDrawCallback(coinPreDrawCallback);
		coin->transformTranslate(glm::vec3(.8f, .8f, 0.f));
		coin->transformScale(glm::vec3(.4f, .4f, .4f));
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::SHOP) {
			static AQ_CompSimpleBox2D* shopBackground = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "ShopBackground");
			static AQ_CompSimpleBox2D* coin = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "Coin");

			shopBackground->draw();
			coin->draw();
		}
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::SHOP) {

		}
	}
	void backgroundPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
	void coinPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
}