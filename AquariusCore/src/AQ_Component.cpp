#include "headers/AQ_Component.hpp"
#include "headers/AQ_GameObject.hpp"

namespace aquarius_engine {
	AQ_GameObject* AQ_Component::getGameObject() {
		return gameObjectThis;
	}
}