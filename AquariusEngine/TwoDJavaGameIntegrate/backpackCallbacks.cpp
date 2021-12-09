
#include "headers\backpackCallbacks.h"
#include "headers/PassingValues.hpp"
#include <headers/AQ_CompBoxInventory2D.hpp>

namespace backpack {
	AQ_CompBoxInventory2D* backpack2D;
	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		backpack2D = gameObjectCtrl->getComponent<AQ_CompBoxInventory2D>(gameObjectThis, "Backpack2D");
		int firstTextureIndex;
		backpack2D->addDiffuseTexture("assets/tempBackpackBack.png", "BackpackBackground",
			GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &firstTextureIndex);
		backpack2D->setSlotTexture("assets/331069-200.png", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true);
		backpack2D->transformTranslate(glm::vec3(.4f, .1f, -.5f));
		backpack2D->transformScale(glm::vec3(1.f, 1.5f, 1.f));
	}

	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::MAINHALL) {
			backpack2D->draw();
		}
	}

	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}
}