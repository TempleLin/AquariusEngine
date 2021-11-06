#include "headers/AQ_GlobalCtrl.hpp"
#include "headers/AQ_Scene.hpp"
#include "headers/AQ_CompInput.hpp"
#include <iostream>

namespace aquarius_engine {
	AQ_GlobalCtrl::AQ_GlobalCtrl() {
		timeCtrl = new TimeCtrl();
		inputSystemCtrl = new AQ_GlobalCtrl::InputSystemCtrl(timeCtrl);
		audioSystemCtrl = new AQ_GlobalCtrl::AudioSystemCtrl();
	}

	AQ_GlobalCtrl::TimeCtrl* AQ_GlobalCtrl::getTimeCtrl() {
		return timeCtrl;
	}

	AQ_GlobalCtrl::InputSystemCtrl* AQ_GlobalCtrl::getInputSystemCtrl() {
		return inputSystemCtrl;
	}

	AQ_GlobalCtrl::AudioSystemCtrl* AQ_GlobalCtrl::getAudioSystemCtrl() {
		return audioSystemCtrl;
	}

	//AQ_GlobalCtrl::LightsCtrl::LightsCtrl(AQ_Scene::Globals::GlobalLights* sceneGlobalLights) {
	//	this->sceneGlobalLights = sceneGlobalLights;
	//}

	//void AQ_GlobalCtrl::LightsCtrl::addDirectionalLight
	//(glm::vec3 direction, glm::vec3 color, float intensity) {
	//	sceneGlobalLights->directionalLights.push_back(AQ_DirLight(direction, color, intensity));
	//}

	//void AQ_GlobalCtrl::LightsCtrl::addPointLight
	//(glm::vec3 position, float radius, float intensity) {
	//	sceneGlobalLights->pointLights.push_back(AQ_PointLight(position, radius, intensity));
	//}

	//void AQ_GlobalCtrl::LightsCtrl::addSpotLight
	//(glm::vec3 position, glm::vec3 direction, float cutoffAngle, float intensity) {
	//	sceneGlobalLights->spotLights.push_back(AQ_SpotLight(position, direction, cutoffAngle, intensity));
	//}

	void AQ_GlobalCtrl::InputSystemCtrl::addInputComp(AQ_CompInput* compInput) {
		allInputComps.push_back(compInput);
	}

	AQ_GlobalCtrl::InputSystemCtrl::InputSystemCtrl(AQ_GlobalCtrl::TimeCtrl* timeCtrlReference) {
		this->timeCtrlReference = timeCtrlReference;
	}

	void AQ_GlobalCtrl::InputSystemCtrl::processInputs() {
		for (int i = 0; i < allInputComps.size(); i++) {
			try {
				auto& currentInputComp = allInputComps.at(i);
				if (allInputComps.at(i)) {
					auto inputToProcess = currentInputComp->processInputs;
					(*inputToProcess)(currentInputComp->belongedWindow, currentInputComp->getGameObject(), timeCtrlReference,
						currentInputComp->inputKeys, currentInputComp->inputActions);
				}
			} catch (const std::bad_function_call& e) {
				std::cout << "ERROR: Input function calling failed--" << e.what() << "\n";
			} catch (...) {
				std::cout << "ERROR: UNKNOWN ERROR IN INPUT FUNCTION CALL" << "\n";
			}
		}
	}

	void AQ_GlobalCtrl::TimeCtrl::updateTime() {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// Count seconds using deltaTime
		iSecondsInGame += deltaTime;
	}

	float AQ_GlobalCtrl::TimeCtrl::getDeltaTime() {
		return deltaTime;
	}

	float AQ_GlobalCtrl::TimeCtrl::getSecondsInGame() {
		return iSecondsInGame;
	}

	AQ_GlobalCtrl::~AQ_GlobalCtrl() {
		delete timeCtrl;
		delete inputSystemCtrl;
		delete audioSystemCtrl;
	}

	AQ_GlobalCtrl::AudioSystemCtrl::AudioSystemCtrl() {
		this->engine = irrklang::createIrrKlangDevice();
	}

	void AQ_GlobalCtrl::AudioSystemCtrl::play2D(std::string path, bool looped) {
		engine->play2D(&path[0], looped);
	}

	void AQ_GlobalCtrl::AudioSystemCtrl::stopAllSounds() {
		engine->stopAllSounds();
	}

	AQ_GlobalCtrl::AudioSystemCtrl::~AudioSystemCtrl() {
		this->engine->drop(); //Delete sound engine.
	}
}