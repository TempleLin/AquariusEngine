#include "headers/AQ_UniControls.h"
#include "headers/AQ_GameObjectCtrl.hpp"
#include "headers/AQ_GlobalCtrl.hpp"

namespace aquarius_engine {
	AQ_UniControls::AQ_UniControls(AQ_Scene* scene) {
		gameObjectCtrl = new AQ_GameObjectCtrl(scene->getGameObjects());
		globalCtrl = new AQ_GlobalCtrl();
	}

	AQ_GameObjectCtrl* AQ_UniControls::getGameObjectCtrl() {
		return gameObjectCtrl;
	}

	AQ_GlobalCtrl* AQ_UniControls::getGlobalCtrl() {
		return globalCtrl;
	}

	AQ_UniControls::~AQ_UniControls() {
		delete gameObjectCtrl;
		delete globalCtrl;
	}
}