#pragma once
#include "AQ_CompSimple2D.hpp"
namespace aquarius_engine {
	class AQ_GameObject;
	class AQ_GameObjectCtrl;

	class AQ_CompButton2D : public AQ_CompSimple2D {
	private:
		void (*onHoverCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl);
		void (*onClickCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl);
	public:
		//AQ_CompButton2D()
		void setListenHover(void (*onHoverCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl)) {}
		void setListenClick(void (*onClickCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl)) {}
	};
}