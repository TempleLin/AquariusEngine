#pragma once
#include <headers/AQ_GameObjectCtrl.hpp>
#include <headers/AQ_GameObject.hpp>
#include <headers/AQ_Component.hpp>

namespace mainCharacter {
	using namespace aquarius_engine;
	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis);
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis);
}