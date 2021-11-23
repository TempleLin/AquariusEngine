#include "headers/AQ_IHoverClick.hpp"

namespace aquarius_engine {
	AQ_IHoverClick::AQ_IHoverClick() : onHoverCallback(nullptr), onClickCallback(nullptr) {

	}
	void AQ_IHoverClick::setListenHover(void (*onHoverCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl)) {
		this->onHoverCallback = onHoverCallback;
	}
	void AQ_IHoverClick::setListenClick(void (*onClickCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl)) {
		this->onClickCallback = onClickCallback;
	}
	bool AQ_IHoverClick::hoverCheck(double cursorX, double cursorY, bool normalized) {
		return false;
	}

	bool AQ_IHoverClick::clickCheck(double cursorX, double cursorY, bool normalized) {
		return false;
	}
	void AQ_IHoverClick::disable(bool disable) {

	}
}