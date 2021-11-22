#include "headers/backpackButtonsCallbacks.h"
#include <string>
#include "headers//shortcutButtonCallbacks.hpp"
#include <headers/AQ_CompBoxButton2D.hpp>
#include <headers/AQ_GlobalCtrl.hpp>
#include <glm/glm.hpp>
#include "headers/glConfigCallbacks.hpp"
#include "headers/CustomButtonComp.hpp"
#include "headers/PassingValues.hpp"

using namespace aquarius_engine;

namespace backpackButtons {
	void backpackBtnPredrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		CustomButtonComp* backPackClotheBtn = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "BackpackClotheBtn2D");
		CustomButtonComp* backpackWeaponsBtn = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "BackpackWeaponsBtn2D");

		int firstButtonTexIndex{};
		backPackClotheBtn->addDiffuseTexture("assets/TempWhiteBtn.png", "ClotheBtnTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &firstButtonTexIndex);
		glm::vec3 btnTopLeft{ -0.5f,  0.5f, .0f };
		glm::vec3 btnTopRight{ 0.5f,  0.5f, .0f };
		glm::vec3 btnBottomRight{ 0.5f, -0.5f, .0f };
		glm::vec3 btnBottomLeft{ -0.5f, -0.5f, .0f };
		backPackClotheBtn->setSensorRange(btnTopLeft, btnTopRight, btnBottomRight, btnBottomLeft);
		backPackClotheBtn->translateSensorRange(glm::vec3(-.1f, 0.5f, 0.f));
		backPackClotheBtn->scaleSensorRange(glm::vec3(.5f, .4f, 1.f));
		backPackClotheBtn->activateTexture(GL_TEXTURE0);
		backPackClotheBtn->setShaderID(shaders.at(0).ID);
		backPackClotheBtn->keepAspectRatio();
		backPackClotheBtn->setPreDrawCallback(backpackBtnPredrawCallback);
		backPackClotheBtn->transformTranslate(glm::vec3(-.1f, 0.5f, 0.f));
		backPackClotheBtn->transformScale(glm::vec3(.5f, .4f, 1.f));

		backpackWeaponsBtn->addDiffuseTexture("assets/TempWhiteBtn.png", "ClotheBtnTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &firstButtonTexIndex);
		backpackWeaponsBtn->setSensorRange(btnTopLeft, btnTopRight, btnBottomRight, btnBottomLeft);
		backpackWeaponsBtn->translateSensorRange(glm::vec3(-.85f, -0.4f, 0.f));
		backpackWeaponsBtn->scaleSensorRange(glm::vec3(.5f, .4f, 1.f));
		backpackWeaponsBtn->activateTexture(GL_TEXTURE0);
		backpackWeaponsBtn->setShaderID(shaders.at(0).ID);
		backpackWeaponsBtn->keepAspectRatio();
		backpackWeaponsBtn->setPreDrawCallback(backpackBtnPredrawCallback);
		backpackWeaponsBtn->transformTranslate(glm::vec3(-.85f, -0.4f, 0.f));
		backpackWeaponsBtn->transformScale(glm::vec3(.5f, .4f, 1.f));
	}

	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		static CustomButtonComp* clotheBtn = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "BackpackClotheBtn2D");
		static CustomButtonComp* weaponsBtn = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "BackpackWeaponsBtn2D");
		clotheBtn->draw();
		weaponsBtn->draw();
	}

	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}

	void processInputs(GLFWwindow* window, AQ_GameObject* gameObjectThis, AQ_GlobalCtrl::TimeCtrl* timeCtrl,
		unsigned int* keys, unsigned int* actions) {
		static AQ_GameObjectCtrl* gameObjectCtrl = gameObjectThis->getGameObjectCtrl();
		static CustomButtonComp* clothButton = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "BackpackClotheBtn2D");
		static CustomButtonComp* weaponsButton = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "BackpackWeaponsBtn2D");

		double mouseXPos, mouseYPos;
		glfwGetCursorPos(window, &mouseXPos, &mouseYPos);

		static bool mouseLeftOnPress{ false };
		switch (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
		case GLFW_PRESS:
			if (!mouseLeftOnPress) {
				static std::string bckgroundTexNames[2]{ "TreeElfBackground", "Background2DTex" };

				bool clothBtnPressed = clothButton->clickCheck(mouseXPos, mouseYPos, false);
				bool weaponsBtnPressed = weaponsButton->clickCheck(mouseXPos, mouseYPos, false);

				if (clothBtnPressed) {
					std::cout << "Pressed cloth button\n";
				}
				if (weaponsBtnPressed) {
					std::cout << "Pressed weapons button\n";
				}

				mouseLeftOnPress = true;
			}
			break;
		case GLFW_RELEASE:
			mouseLeftOnPress = false;
			break;
		}
	}

	void backpackBtnPredrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
}