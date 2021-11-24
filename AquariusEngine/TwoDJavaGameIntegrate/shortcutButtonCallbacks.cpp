#include <string>
#include "headers/shortcutButtonCallbacks.hpp"
#include <headers/AQ_CompBoxButton2D.hpp>
#include <headers/AQ_GlobalCtrl.hpp>
#include <glm/glm.hpp>
#include "headers/glConfigCallbacks.hpp"
#include "headers/CustomButtonComp.hpp"
#include "headers/PassingValues.hpp"

namespace shortcutButton {
	using namespace aquarius_engine;
	void shortcutButtonPredrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);

	CustomButtonComp* mainhallBtn;
	CustomButtonComp* missionBtn;
	CustomButtonComp* attackBtn;
	CustomButtonComp* shopBtn;
	CustomButtonComp* statusBtn;

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		mainhallBtn = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "MainHallButton2D");
		missionBtn = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "MissionButton2D");
		attackBtn = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "AttackButton2D");
		shopBtn = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "ShopButton2D");
		statusBtn = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "StatusButton2D");

		int shortcutButtonTexIndex{};
		mainhallBtn->addDiffuseTexture("assets/TempShortcuts/MainHall.png", "MainhallDiffuse", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &shortcutButtonTexIndex);
		glm::vec3 topLeft{ -0.5f,  0.5f, .0f };
		glm::vec3 topRight{ 0.5f,  0.5f, .0f };
		glm::vec3 bottomRight{ 0.5f, -0.5f, .0f };
		glm::vec3 bottomLeft{ -0.5f, -0.5f, .0f };
		mainhallBtn->setSensorRange(topLeft, topRight, bottomRight, bottomLeft);
		mainhallBtn->translateSensorRange(glm::vec3(0.f, -.8f, 0.f));
		mainhallBtn->scaleSensorRange(glm::vec3(.35f, .35f, 1.f));
		mainhallBtn->setShaderID(shaders.at(0).ID);
		mainhallBtn->keepAspectRatio();
		mainhallBtn->setPreDrawCallback(shortcutButtonPredrawCallback);
		mainhallBtn->transformTranslate(glm::vec3(0.f, -.8f, 0.f));
		mainhallBtn->transformScale(glm::vec3(.35f, .35f, 1.f));

		missionBtn->addDiffuseTexture("assets/Shortcuts/Mission.png", "MissionDiffuse", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &shortcutButtonTexIndex);
		missionBtn->setSensorRange(topLeft, topRight, bottomRight, bottomLeft);
		missionBtn->translateSensorRange(glm::vec3(.2f, -.8f, 0.f));
		missionBtn->scaleSensorRange(glm::vec3(.35f, .35f, 1.f));
		missionBtn->setShaderID(shaders.at(0).ID);
		missionBtn->keepAspectRatio();
		missionBtn->setPreDrawCallback(shortcutButtonPredrawCallback);
		missionBtn->transformTranslate(glm::vec3(.2f, -.8f, 0.f));
		missionBtn->transformScale(glm::vec3(.35f, .35f, 1.f));

		attackBtn->addDiffuseTexture("assets/TempShortcuts/Attack.png", "AttackDiffuse", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &shortcutButtonTexIndex);
		attackBtn->setSensorRange(topLeft, topRight, bottomRight, bottomLeft);
		attackBtn->translateSensorRange(glm::vec3(.4f, -.8f, 0.f));
		attackBtn->scaleSensorRange(glm::vec3(.35f, .35f, 1.f));
		attackBtn->setShaderID(shaders.at(0).ID);
		attackBtn->keepAspectRatio();
		attackBtn->setPreDrawCallback(shortcutButtonPredrawCallback);
		attackBtn->transformTranslate(glm::vec3(.4f, -.8f, 0.f));
		attackBtn->transformScale(glm::vec3(.35f, .35f, 1.f));

		shopBtn->addDiffuseTexture("assets/Shortcuts/Shop.png", "ShopDiffuse", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &shortcutButtonTexIndex);
		shopBtn->setSensorRange(topLeft, topRight, bottomRight, bottomLeft);
		shopBtn->translateSensorRange(glm::vec3(.6f, -.8f, 0.f));
		shopBtn->scaleSensorRange(glm::vec3(.35f, .35f, 1.f));
		shopBtn->setShaderID(shaders.at(0).ID);
		shopBtn->keepAspectRatio();
		shopBtn->setPreDrawCallback(shortcutButtonPredrawCallback);
		shopBtn->transformTranslate(glm::vec3(.6f, -.8f, 0.f));
		shopBtn->transformScale(glm::vec3(.35f, .35f, 1.f));

		statusBtn->addDiffuseTexture("assets/Shortcuts/Status.png", "ShopDiffuse", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &shortcutButtonTexIndex);
		statusBtn->setSensorRange(topLeft, topRight, bottomRight, bottomLeft);
		statusBtn->translateSensorRange(glm::vec3(.8f, -.8f, 0.f));
		statusBtn->scaleSensorRange(glm::vec3(.35f, .35f, 1.f));
		statusBtn->setShaderID(shaders.at(0).ID);
		statusBtn->keepAspectRatio();
		statusBtn->setPreDrawCallback(shortcutButtonPredrawCallback);
		statusBtn->transformTranslate(glm::vec3(.8f, -.8f, 0.f));
		statusBtn->transformScale(glm::vec3(.35f, .35f, 1.f));
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		mainhallBtn->draw();
		missionBtn->draw();
		attackBtn->draw();
		shopBtn->draw();
		statusBtn->draw();
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}

	void processInputs(GLFWwindow* window, AQ_GameObject* gameObjectThis, AQ_GlobalCtrl::TimeCtrl* timeCtrl,
		unsigned int* keys, unsigned int* actions) {
		static AQ_GameObjectCtrl* gameObjectCtrl = gameObjectThis->getGameObjectCtrl();
		static CustomButtonComp* buttons[]{ 
			mainhallBtn,
			missionBtn,
			attackBtn,
			shopBtn,
			statusBtn
		};
		static AQ_GameObject* background = gameObjectCtrl->getGameObject("Background");
		static AQ_CompSimpleBox2D* background2D = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(background, "Background2D");

		static AQ_GameObject* shopObject = gameObjectCtrl->getGameObject("ShopObject");

		static bool mouseLeftOnPress{ false };

		double mouseXPos, mouseYPos;
		glfwGetCursorPos(window, &mouseXPos, &mouseYPos);

		static bool expand[]{ true, true, true, true, true };

		for (int i = 0; i < sizeof(expand) / sizeof(bool); i++) {
			bool onHover = buttons[i]->hoverCheck(mouseXPos, mouseYPos, false);

			if (onHover && expand[i]) {
				/*if (movementOffset < .75f) {
					movementOffset += 0.05f;
					gameObjectThis->transformTranslate(glm::vec3(.05f, 0.f, 0.f));
				}*/
				buttons[i]->transformScale(glm::vec3(1.2f, 1.2f, 1.f));
				expand[i] = false;
			} else if (!onHover && !expand[i]) {
				//gameObjectThis->transformTranslate(glm::vec3(-movementOffset, 0.f, 0.f));
				buttons[i]->transformScale(glm::vec3(1.f / 1.2f, 1.f / 1.2f, 1.f));
				//movementOffset = 0.f;
				expand[i] = true;
			}
		}


		switch (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
		case GLFW_PRESS:
			if (!mouseLeftOnPress) {
				if (buttons[0]->clickCheck(mouseXPos, mouseYPos, false)) {
					std::cout << "Mainhall btn pressed\n";
					currentScene = CurrentScene::MAINHALL;
				} else if (buttons[1]->clickCheck(mouseXPos, mouseYPos, false)) {
					std::cout << "Mission btn pressed\n";
					currentScene = CurrentScene::MISSION;
				} else if (buttons[2]->clickCheck(mouseXPos, mouseYPos, false)) {
					std::cout << "Attack btn pressed\n";
					currentScene = CurrentScene::ATTACK;
				} else if (buttons[3]->clickCheck(mouseXPos, mouseYPos, false)) {
					std::cout << "Shop btn pressed\n";
					currentScene = CurrentScene::SHOP;
				} else if (buttons[4]->clickCheck(mouseXPos, mouseYPos, false)) {
					std::cout << "Status btn pressed\n";
					currentScene = CurrentScene::STATUS;
				}
				mouseLeftOnPress = true;
			}
			break;
		case GLFW_RELEASE:
			mouseLeftOnPress = false;
			break;
		}
	}

	void shortcutButtonPredrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
}