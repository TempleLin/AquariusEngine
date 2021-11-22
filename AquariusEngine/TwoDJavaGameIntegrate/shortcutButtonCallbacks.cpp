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

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		CustomButtonComp* shortcutBtn = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "ShortcutButton2D");

		int shortcutButtonTexIndex{};
		shortcutBtn->addDiffuseTexture("assets/tempButton.png", "ShortcutButton2D", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &shortcutButtonTexIndex);
		glm::vec3 topLeft{ -0.5f,  0.5f, .0f };
		glm::vec3 topRight{ 0.5f,  0.5f, .0f };
		glm::vec3 bottomRight{ 0.5f, -0.5f, .0f };
		glm::vec3 bottomLeft{ -0.5f, -0.5f, .0f };
		shortcutBtn->setSensorRange(topLeft, topRight, bottomRight, bottomLeft);
		shortcutBtn->translateSensorRange(glm::vec3(-.9f, -.8f, 0.f));
		shortcutBtn->scaleSensorRange(glm::vec3(1.f, .4f, 1.f));
		shortcutBtn->activateTexture(GL_TEXTURE0);
		shortcutBtn->setShaderID(shaders.at(0).ID);
		shortcutBtn->keepAspectRatio();
		shortcutBtn->setPreDrawCallback(shortcutButtonPredrawCallback);
		shortcutBtn->transformTranslate(glm::vec3(-.9f, -.8f, 0.f));
		shortcutBtn->transformScale(glm::vec3(1.f, .4f, 1.f));
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		static CustomButtonComp* firstBtn2D = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "ShortcutButton2D");
		firstBtn2D->draw();
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}

	void processInputs(GLFWwindow* window, AQ_GameObject* gameObjectThis, AQ_GlobalCtrl::TimeCtrl* timeCtrl,
		unsigned int* keys, unsigned int* actions) {
		static AQ_GameObjectCtrl* gameObjectCtrl = gameObjectThis->getGameObjectCtrl();
		static CustomButtonComp* shortcutButton = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "ShortcutButton2D");
		static AQ_GameObject* background = gameObjectCtrl->getGameObject("Background");
		static AQ_CompSimpleBox2D* background2D = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(background, "Background2D");

		static bool mouseLeftOnPress{ false };

		double mouseXPos, mouseYPos;
		glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
		bool onHover = shortcutButton->hoverCheck(mouseXPos, mouseYPos, false);

		static float movementOffset{ 0.f };
		if (onHover) {
			if (movementOffset < .75f) {
				movementOffset += 0.05f;
				gameObjectThis->transformTranslate(glm::vec3(.05f, 0.f, 0.f));
			}
		} else {
			gameObjectThis->transformTranslate(glm::vec3(-movementOffset, 0.f, 0.f));
			movementOffset = 0.f;
		}

		switch (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
		case GLFW_PRESS:
			if (!mouseLeftOnPress) {
				static std::string bckgroundTexNames[2]{ "TreeElfBackground", "Background2DTex" };
				static int currentIndex{ 0 };

				bool pressSuccess = shortcutButton->clickCheck(mouseXPos, mouseYPos, false);
				if (pressSuccess) {
					background2D->switchDiffuseTexture(bckgroundTexNames[currentIndex]);
					++currentIndex %= 2;
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