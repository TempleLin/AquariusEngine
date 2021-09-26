#pragma once
#include "AQ_CompModel.h"
#include "AQ_CompCamera.h"
#include "AQ_Lights.h"

#include <map>
#include <vector>
#include <iostream>
class AQ_Component;

class AQ_DataBase {
	friend class AQ_GameObject;
	friend class AQ_GlobalCtrl;
	friend class LightsCtrl;
	friend class AQ_GameObjectCtrl;
private:
	static class Components {
		friend class AQ_GameObject;
		friend class AQ_GameObjectCtrl;
	private:
		// @currentKey will keep += 1 and never repeat for every keys throughout database
		static unsigned int currentKeyIndex;
		static std::map<unsigned int, AQ_CompModel> modelComponents;
		static std::map<unsigned int, AQ_CompCamera> cameraComponents;

		static void addCameraComponent(AQ_CompCamera component, unsigned int& returnKey) {
			cameraComponents.insert(std::pair<unsigned int, AQ_CompCamera>(currentKeyIndex, component));
			returnKey = currentKeyIndex;
			currentKeyIndex++;
		}

		static void addModelComponent(AQ_CompModel component, unsigned int& returnKey) {
			modelComponents.insert(std::pair<unsigned int, AQ_CompModel>(currentKeyIndex, component));
			returnKey = currentKeyIndex;
			currentKeyIndex++;
		}

		static AQ_CompCamera& getCameraComponent(unsigned int key) {
			return cameraComponents.find(key)->second;
		}

		static AQ_CompModel& getModelComponent(unsigned int key) {
			return modelComponents.find(key)->second;
		}
	};

	static class GlobalLights {
		friend class AQ_GlobalCtrl;
		friend class LightsCtrl;
	private:
		static std::vector<AQ_DirLight> directionalLights;
		static std::vector<AQ_PointLight> pointLights;
		static std::vector<AQ_SpotLight> spotLights;
	};
};