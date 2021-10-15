#include "headers/AQ_CompInput.hpp"
#include "headers/AQ_GlobalCtrl.hpp"
namespace aquarius_engine {
	AQ_CompInput::AQ_CompInput(GLFWwindow* belongedWindow, AQ_GameObject** gameObjectsToAffect, unsigned int gameObjectsCount,
		std::function<void(GLFWwindow* window, AQ_GameObject**, AQ_GlobalCtrl::TimeCtrl* timeCtrl)>* processInputsCallBack,
		AQ_GlobalCtrl::InputSystemCtrl& inputSystemCtrl) {
		this->belongedWindow = belongedWindow;
		this->gameObjectsToAffect = gameObjectsToAffect;
		this->gameObjectsCount = gameObjectsCount;
		this->processInputs = processInputsCallBack;
		inputSystemCtrl.addInputComp(this);
		this->pointerToInputSystemCtrl = &inputSystemCtrl;
	}

	AQ_CompInput::~AQ_CompInput() {
		unsigned int totalOfAllInputUnits = pointerToInputSystemCtrl->allInputComps.size();
		auto& holderToAllInputCompsPtrs = pointerToInputSystemCtrl->allInputComps;
		for (int i = 0; i < totalOfAllInputUnits; i++) {
			if (holderToAllInputCompsPtrs.at(i) == this) {
				holderToAllInputCompsPtrs.erase(holderToAllInputCompsPtrs.begin() + i);
			}
		}
		delete[] gameObjectsToAffect;
		delete processInputs;
	}
}