#pragma once
#include "AQ_CompModel.h"
#include "AQ_CompCamera.h"
#include "AQ_Lights.h"

#include <map>
#include <vector>
#include <iostream>
class AQ_Component;

class AQ_Database {
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

		static void addCameraComponent(AQ_CompCamera& component, unsigned int& returnKey);
		static void addModelComponent(AQ_CompModel& component, unsigned int& returnKey);
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