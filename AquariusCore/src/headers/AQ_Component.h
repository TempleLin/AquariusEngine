#pragma once
#include <typeinfo>
#include <string>

enum class AQ_EComponents {
	CAMERA, MODEL
};

class AQ_Component {
	friend class AQ_GameObject;
	friend class AQ_GameObjectCtrl;
protected:
	unsigned int databaseAccessKey;
	std::string name;
};