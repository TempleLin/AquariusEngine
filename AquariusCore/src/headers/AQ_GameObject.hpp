#pragma once
#include <string>
#include <map>
#include <vector>
#include <type_traits>
#include <typeindex>
#include <utility>

#include "AQ_Database.hpp"
#include "AQ_Component.hpp"
namespace aquarius_engine {
	class AQ_GameObjectCtrl;
	class AQ_CompModel;

	class AQ_GameObject {
		friend class AQ_GameObjectCtrl;
	private:
		AQ_GameObjectCtrl* gameObjectCtrlPtr;
		std::string name;
		std::map<std::type_index, std::vector<std::pair<std::string, void*>>> components;
	public:
		AQ_GameObject(AQ_GameObjectCtrl* gameObjectCtrl, std::string name);
		~AQ_GameObject();
	};
}