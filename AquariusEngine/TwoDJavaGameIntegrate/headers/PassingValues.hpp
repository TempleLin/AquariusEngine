#pragma once
#include <vector>
#include <headers/AQ_Shader.hpp>
#include <headers/AQ_GlobalCtrl.hpp>

namespace aquarius_engine {
	extern std::vector<AQ_Shader> shaders;
	extern AQ_GlobalCtrl::TimeCtrl* timeCtrlRef;


	enum class CurrentScene {
		MAINHALL,
		MISSION,
		ATTACK,
		SHOP,
		STATUS
	};
	extern CurrentScene currentScene;


	enum class AttackMode {
		SELECTING,
		ATTACKING0,
		ATTACKING1
	};
	extern AttackMode attackMode;
}
