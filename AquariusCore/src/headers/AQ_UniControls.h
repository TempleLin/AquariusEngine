#pragma once

namespace aquarius_engine {
	class AQ_GameObjectCtrl;
	class AQ_GlobalCtrl;

	class AQ_UniControls {
	private:
		AQ_GameObjectCtrl* gameObjectCtrlReference;
		AQ_GlobalCtrl* globalCtrlReference;
	public:
		AQ_UniControls();
		AQ_GameObjectCtrl* createGameObjectCtrl();
		AQ_GlobalCtrl* createGlobalCtrl();
		AQ_GameObjectCtrl* getGameObjectCtrl();
		AQ_GlobalCtrl* getGlobalCtrl();
	};
}