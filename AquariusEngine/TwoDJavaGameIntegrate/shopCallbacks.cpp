#include "headers/shopCallbacks.h"
#include "headers/PassingValues.hpp"
#include <headers/AQ_GameObjectCtrl.hpp>
#include <headers/AQ_GameObject.hpp>
#include <headers/AQ_CompSimpleBox2D.hpp>

namespace shop {
	using namespace aquarius_engine;
	AQ_CompSimpleBox2D* shopBackground;
	AQ_CompSimpleBox2D* coin;
	AQ_CompSimpleBox2D* clerk;

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		shopBackground = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "ShopBackground");
		coin = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "Coin");
		clerk = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "Clerk");

		int returnTextIndex{};
		shopBackground->addDiffuseTexture("assets/ShopBackground.png", "ShopBackgroundImageText", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
			true, &returnTextIndex);
		shopBackground->transformScale(glm::vec3(2.f, 2.f, 1.f));

		coin->addDiffuseTexture("assets/Coin.png", "Coin2DTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &returnTextIndex);
		coin->transformTranslate(glm::vec3(.8f, .8f, -1.f));
		coin->transformScale(glm::vec3(.4f, .4f, .4f));
		coin->keepAspectRatio();

		clerk->addDiffuseTexture("assets/Clerk.png", "ClerkTexImage", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &returnTextIndex);
		clerk->keepAspectRatio();
		clerk->transformScale(glm::vec3(1.5f, 2.2f, 1.f));
		clerk->transformTranslate(glm::vec3(.4f, -.25f, -1.f));
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::SHOP) {
			shopBackground->draw();
			coin->draw();
			clerk->draw();
		}
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::SHOP) {

		}
	}
}