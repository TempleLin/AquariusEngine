#include "headers/AQ_CompInput.h"
#include "headers/AQ_GlobalCtrl.h"
#include <iostream>
#include <stdexcept>

AQ_CompInput::AQ_CompInput(AQ_GameObject** gameObjectsToAffect, std::function<void()>* processInputs, AQ_GlobalCtrl::InputSystemCtrl& inputSystemCtrl) {
	this->gameObjectsToAffect = gameObjectsToAffect;
	this->processInputs = processInputs;
	inputSystemCtrl.addInputComp(*this);
	this->pointerToInputSystemCtrl = &inputSystemCtrl;
}

//AQ_CompInput::~AQ_CompInput() {
//	unsigned int totalOfAllInputUnits = pointerToInputSystemCtrl->allInputComps.size();
//	auto& holderToAllInputCompsPtrs = pointerToInputSystemCtrl->allInputComps;
//	for (int i = 0; i < totalOfAllInputUnits; i++) {
//		if (holderToAllInputCompsPtrs.at(i) == this) {
//			holderToAllInputCompsPtrs.erase(holderToAllInputCompsPtrs.begin() + i);
//		}
//	}
//	delete this->processInputs;
//}