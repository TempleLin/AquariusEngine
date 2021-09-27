#pragma once
#include <map>
#include <type_traits>

#include "AQ_Database.h"
#include "AQ_Component.h"
class AQ_CompModel;

class AQ_GameObject {
	friend class AQ_GameObjectCtrl;
private:
	std::map<AQ_EComponents, std::vector<unsigned int>> componentsKeys;
};