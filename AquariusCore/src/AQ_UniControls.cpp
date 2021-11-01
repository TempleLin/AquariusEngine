#include "headers/AQ_UniControls.h"
#include "headers/AQ_GameObjectCtrl.hpp"
#include "headers/AQ_GlobalCtrl.hpp"

namespace aquarius_engine {
	AQ_UniControls::AQ_UniControls(AQ_Scene* scene) {
		gameObjectCtrlReference = new AQ_GameObjectCtrl(scene->getGameObjects());
		globalCtrlReference = new AQ_GlobalCtrl();
	}

	AQ_GameObjectCtrl* AQ_UniControls::getGameObjectCtrl() {
		return gameObjectCtrlReference;
	}

	AQ_GlobalCtrl* AQ_UniControls::getGlobalCtrl() {
		return globalCtrlReference;
	}

	AQ_UniControls::~AQ_UniControls() {
		delete gameObjectCtrlReference;
		delete globalCtrlReference;
	}
}