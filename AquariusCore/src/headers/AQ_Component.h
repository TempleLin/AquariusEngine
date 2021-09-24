#pragma once
#include <typeinfo>

class AQ_Component {
	friend class AQ_GameObject;
protected:
	const std::type_info& type;
	unsigned int dataBaseAcessKey;
public:
	AQ_Component(const std::type_info& _type);
};