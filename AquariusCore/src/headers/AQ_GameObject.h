#pragma once
#include <map>
#include <type_traits>
#include <typeindex>

#include "AQ_Database.h"
#include "AQ_Component.h"
class AQ_CompModel;

class AQ_GameObject {
	friend class AQ_GameObjectCtrl;
private:
	std::map<std::type_index, std::vector<unsigned int>> componentsKeys;
};