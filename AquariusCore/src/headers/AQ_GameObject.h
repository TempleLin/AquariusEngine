#pragma once
#include <string>
#include <map>
#include <vector>
#include <type_traits>
#include <typeindex>
#include <utility>

#include "AQ_Database.h"
#include "AQ_Component.h"
class AQ_Model;

class AQ_GameObject {
	friend class AQ_GameObjectCtrl;
private:
	std::map<std::type_index, std::vector<std::pair<std::string, unsigned int>>> componentsKeys;
public:
	~AQ_GameObject();
};