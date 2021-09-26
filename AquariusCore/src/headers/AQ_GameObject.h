#pragma once
#include <map>
#include <vector>
#include <type_traits>

#include "AQ_Database.h"
#include "AQ_Component.h"
class AQ_CompModel;

class AQ_GameObject {
	friend class AQ_GameObjectCtrl;
private:
	std::vector<AQ_Component> components;
};