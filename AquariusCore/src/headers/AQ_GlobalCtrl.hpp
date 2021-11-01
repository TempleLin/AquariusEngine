#pragma once
#include "AQ_Scene.hpp"
#include <vector>
#include <glm/glm.hpp>

namespace aquarius_engine {
	class AQ_CompInput;

	class AQ_GlobalCtrl {
	public:
		class TimeCtrl {
		private:
			float deltaTime;
			float lastFrame;
			float currentFrame;
			float iSecondsInGame;
		public:
			void updateTime();
			float getDeltaTime();
			float getSecondsInGame();
		};
		class LightsCtrl {
		private:
			AQ_Scene::GlobalLights* databaseGlobalLights;
		public:
			LightsCtrl(AQ_Scene::GlobalLights* databaseGlobalLights);
			void addDirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity);
			void addPointLight(glm::vec3 position, float radius, float intensity);
			void addSpotLight(glm::vec3 position, glm::vec3 direction, float cutoffAngle, float intensity);
		};
		class InputSystemCtrl {
			friend class AQ_CompInput;
		private:
			std::vector<AQ_CompInput*> allInputComps;
			AQ_GlobalCtrl::TimeCtrl* timeCtrlReference;
			void addInputComp(AQ_CompInput* compInput);
		public:
			InputSystemCtrl(AQ_GlobalCtrl::TimeCtrl* timeCtrlReference);
			void processInputs();
		};
	};
}