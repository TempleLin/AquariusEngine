#include "headers/missionCallbacks.h"
#include "headers/PassingValues.hpp"
#include <headers/AQ_CompBoxButton2D.hpp>
#include <headers/AQ_GlobalCtrl.hpp>

#include "dear_imgui/imgui.h"
#include "dear_imgui/imgui_impl_glfw.h"
#include "dear_imgui/imgui_impl_opengl3.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

namespace mission {
	void missionBoardPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);

	AQ_CompSimpleBox2D* missionBoard;

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		missionBoard = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "MissionBoard");
		int returnTexIndex{};
		missionBoard->addDiffuseTexture("assets/MissionBoard.png", "MissionBoardTexImage", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
			true, &returnTexIndex);
		missionBoard->setShaderID(shaders.at(0).ID);
		missionBoard->setPreDrawCallback(missionBoardPreDrawCallback);
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::MISSION) {
			static AQ_GlobalCtrl::TimeCtrl* timeCtrl = gameObjectCtrl->getUniControls()->getGlobalCtrl()->getTimeCtrl();
			missionBoard->draw();

			{
				static bool startMission{ false };

				ImGui::Begin("Setup a Mission");
				ImVec2 windowSize(400.f, 110.f);
				ImGui::SetWindowSize(windowSize);
				static float hours;
				ImGui::SliderFloat("Hours to Spend", &hours, 0.0f, 24.0f);
				static char subject[100];
				ImGui::InputText("Enter your subject", subject, sizeof(subject));
				if (ImGui::Button("Start")) {
					startMission = true;
				}
				ImGui::End();

				if (startMission) {
					ImGui::Begin(subject);
					static float lastTimeCount{ 0.f };
					float currentTime = glfwGetTime();
					if (currentTime - lastTimeCount >= 1.f) {
						hours -= (currentTime / 3600.f);
						lastTimeCount = currentTime;
					}
					ImGui::Text("Time left: %f hours", hours);
					ImGui::End();
				}
			}
		}
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}

	void missionBoardPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
}