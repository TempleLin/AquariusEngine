#include "headers/missionCallbacks.h"
#include "headers/PassingValues.hpp"
#include <headers/AQ_CompBoxButton2D.hpp>

namespace mission {
	void missionBoardPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		AQ_CompSimpleBox2D* missionBoard = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "MissionBoard");
		int returnTexIndex{};
		missionBoard->addDiffuseTexture("assets/MissionBoard.png", "MissionBoardTexImage", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
			true, &returnTexIndex);
		missionBoard->activateTexture(GL_TEXTURE0);
		missionBoard->setShaderID(shaders.at(0).ID);
		missionBoard->setPreDrawCallback(missionBoardPreDrawCallback);
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::MISSION) {
			static AQ_CompSimpleBox2D* missionBoard = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "MissionBoard");
			missionBoard->draw();
		}
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}

	void missionBoardPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
}