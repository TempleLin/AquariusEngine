#pragma once
#include "AQ_Scene.hpp"

namespace aquarius_engine {
	class AQ_GameObjectCtrl;
	class AQ_GlobalCtrl;

	class AQ_UniControls {
	private:
		AQ_GameObjectCtrl* gameObjectCtrl;
		AQ_GlobalCtrl* globalCtrl;
	public:
		AQ_UniControls(AQ_Scene* scene);
		AQ_GameObjectCtrl* getGameObjectCtrl();
		AQ_GlobalCtrl* getGlobalCtrl();
		~AQ_UniControls();
	};
}