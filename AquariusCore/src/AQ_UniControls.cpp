#include "headers/AQ_UniControls.h"
#include "headers/AQ_GameObjectCtrl.hpp"
#include "headers/AQ_GlobalCtrl.hpp"

namespace aquarius_engine {
	AQ_UniControls::AQ_UniControls() : gameObjectCtrlReference(nullptr), globalCtrlReference(nullptr) {

	}

	AQ_GameObjectCtrl* AQ_UniControls::createGameObjectCtrl() {
		//gameObjectCtrlReference = new AQ_GameObjectCtrl()
	}
}