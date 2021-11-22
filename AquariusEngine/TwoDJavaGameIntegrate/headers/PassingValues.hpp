#pragma once
#include <vector>
#include <headers/AQ_Shader.hpp>
#include <headers/AQ_GlobalCtrl.hpp>

namespace aquarius_engine {
	extern std::vector<AQ_Shader> shaders;
	extern AQ_GlobalCtrl::TimeCtrl* timeCtrlRef;


	enum class CurrentScene {
		MAINHALL,
		SHOP
	};
	extern CurrentScene currentScene;
}
