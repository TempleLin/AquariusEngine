#pragma once
#include "AQ_GameObjectCtrl.hpp"
#include "AQ_GameObject.hpp"
#include <glm/glm.hpp>

namespace aquarius_engine {
	class AQ_IHoverClick {
	protected:
		void (*onHoverCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl);
		void (*onClickCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl);
	public:
		AQ_IHoverClick();
		void setListenHover(void (*onHoverCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl));
		void setListenClick(void (*onClickCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl));
		virtual bool hoverCheck(double cursorX, double cursorY, bool normalized);
		virtual bool clickCheck(double cursorX, double cursorY, bool normalized);
		virtual void disable(bool disable);
	};
}