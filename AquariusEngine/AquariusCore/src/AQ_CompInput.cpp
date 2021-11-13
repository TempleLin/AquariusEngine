#include "headers/AQ_CompInput.hpp"
#include "headers/AQ_GlobalCtrl.hpp"
namespace aquarius_engine {
	AQ_CompInput::AQ_CompInput(GLFWwindow* belongedWindow, unsigned int* inputKeys,
		unsigned int* inputActions, void (*callbackProcessInputs)(GLFWwindow* window, AQ_GameObject* gameObjectThis, 
			AQ_GlobalCtrl::TimeCtrl* timeCtrl, unsigned int* keys, unsigned int* actions),
		AQ_GlobalCtrl::InputSystemCtrl* inputSystemCtrl) {
		this->belongedWindow = belongedWindow;
		this->processInputs = callbackProcessInputs;
		this->inputKeys = inputKeys;
		this->inputActions = inputActions;
		inputSystemCtrl->addInputComp(this);
		this->pointerToInputSystemCtrl = inputSystemCtrl;
	}

	AQ_CompInput::~AQ_CompInput() {
		AQ_Component::~AQ_Component();
		unsigned int totalOfAllInputUnits = pointerToInputSystemCtrl->allInputComps.size();
		auto& holderToAllInputCompsPtrs = pointerToInputSystemCtrl->allInputComps;
		for (int i = 0; i < totalOfAllInputUnits; i++) {
			if (holderToAllInputCompsPtrs.at(i) == this) {
				holderToAllInputCompsPtrs.erase(holderToAllInputCompsPtrs.begin() + i);
			}
		}
		delete[] inputKeys;
		delete[] inputActions;
	}

	void AQ_CompInput::rebindCallBack(void (*callbackProcessInputs)(GLFWwindow* window, AQ_GameObject* gameObjectThis, AQ_GlobalCtrl::TimeCtrl* timeCtrl,
		unsigned int* keys, unsigned int* actions)) {
		this->processInputs = callbackProcessInputs;
	}

	void AQ_CompInput::rebindInputKeys(unsigned int* inputKeys) {
		delete[] this->inputKeys;
		this->inputKeys = inputKeys;
	}

	void AQ_CompInput::rebindInputActions(unsigned int* inputActions) {
		delete[] this->inputActions;
		this->inputActions = inputActions;
	}
}