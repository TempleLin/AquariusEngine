#pragma once
#include <vector>
#include <functional>
#include <memory>
#include "AQ_GameObject.h"
#include "AQ_GlobalCtrl.h"
#include "AQ_Component.h"

class AQ_CompInput : public AQ_Component{
	friend class AQ_GlobalCtrl;
	friend class InputSystemCtrl;
private:
	AQ_GameObject** gameObjectsToAffect;
	AQ_GlobalCtrl::InputSystemCtrl* pointerToInputSystemCtrl;
public:
	AQ_CompInput(AQ_GameObject** gameObjectsToAffect, std::function<void()>* processInputs, AQ_GlobalCtrl::InputSystemCtrl& inputSystemCtrl);
	std::function<void()>* processInputs;
	//~AQ_CompInput();
};