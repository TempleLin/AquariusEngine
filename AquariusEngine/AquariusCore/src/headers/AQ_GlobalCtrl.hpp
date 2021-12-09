#pragma once
#include "AQ_Scene.hpp"
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <irrKlang/irrKlang.h>

namespace aquarius_engine {
	class AQ_CompInput;

	class AQ_GlobalCtrl {
		friend class AQ_UniControls;
		class TimeCtrl;
		//class LightsCtrl;
		class InputSystemCtrl;
		class AudioSystemCtrl;
	private:
		TimeCtrl* timeCtrl;
		InputSystemCtrl* inputSystemCtrl;
		AudioSystemCtrl* audioSystemCtrl;
		//LightsCtrl* lightsCtrl;
		AQ_GlobalCtrl();
	public:
		TimeCtrl* getTimeCtrl();
		InputSystemCtrl* getInputSystemCtrl();
		AudioSystemCtrl* getAudioSystemCtrl();
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
			float getFPS();
		};
		/*class LightsCtrl {
		private:
			AQ_Scene::Globals::GlobalLights* sceneGlobalLights;
		public:
			LightsCtrl(AQ_Scene* scene);
			void addDirectionalLight(glm::vec3 direction, glm::vec3 color, float intensity);
			void addPointLight(glm::vec3 position, float radius, float intensity);
			void addSpotLight(glm::vec3 position, glm::vec3 direction, float cutoffAngle, float intensity);
		};*/
		class InputSystemCtrl {
			friend class AQ_CompInput;
		private:
			std::vector<AQ_CompInput*> allInputComps;
			AQ_GlobalCtrl::TimeCtrl* timeCtrlReference;
			/*
			* @Gets called from AQ_CompButton2D.
			*/
			void addInputComp(AQ_CompInput* compInput);
		public:
			InputSystemCtrl(AQ_GlobalCtrl::TimeCtrl* timeCtrlReference);
			void processInputs();
		};

		class AudioSystemCtrl {
		private:
			irrklang::ISoundEngine* engine;
		public:
			AudioSystemCtrl();
			void play2D(std::string path, bool looped);
			void stopAllSounds();
			~AudioSystemCtrl();
		};
		~AQ_GlobalCtrl();
	};
}