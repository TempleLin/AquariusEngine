#include <string>
#include "headers/firstButtonCallbacks.hpp"
#include <headers/AQ_CompBoxButton2D.hpp>
#include <headers/AQ_GlobalCtrl.hpp>
#include <glm/glm.hpp>
#include "headers/glConfigCallbacks.hpp"
#include "headers/CustomButtonComp.hpp"
#include "headers/PassingValues.hpp"

namespace firstButton {
	void firstButtonPredrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		CustomButtonComp* firstBtn2D = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "FirstButton2D");

		int firstButtonTexIndex{};
		firstBtn2D->addDiffuseTexture("assets/tempButton.png", "FirstButton2D", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &firstButtonTexIndex);
		glm::vec3 topLeft{ -0.5f,  0.5f, .0f };
		glm::vec3 topRight{ 0.5f,  0.5f, .0f };
		glm::vec3 bottomRight{ 0.5f, -0.5f, .0f };
		glm::vec3 bottomLeft{ -0.5f, -0.5f, .0f };
		firstBtn2D->setSensorRange(topLeft, topRight, bottomRight, bottomLeft);
		firstBtn2D->translateSensorRange(glm::vec3(.5f, 0.f, 0.f));
		firstBtn2D->scaleSensorRange(glm::vec3(1.f, .4f, 1.f));
		firstBtn2D->activateTexture(GL_TEXTURE0);
		firstBtn2D->setShaderID(shaders.at(0).ID);
		firstBtn2D->keepAspectRatio();
		firstBtn2D->setPreDrawCallback(firstButtonPredrawCallback);
		firstBtn2D->transformTranslate(glm::vec3(.5f, 0.f, 0.f));
		firstBtn2D->transformScale(glm::vec3(1.f, .4f, 1.f));
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		static CustomButtonComp* firstBtn2D = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "FirstButton2D");
		firstBtn2D->draw();
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}

	void processInputs(GLFWwindow* window, AQ_GameObject* gameObjectThis, AQ_GlobalCtrl::TimeCtrl* timeCtrl,
		unsigned int* keys, unsigned int* actions) {
		static AQ_GameObjectCtrl* gameObjectCtrl = gameObjectThis->getGameObjectCtrl();
		static CustomButtonComp* firstButton = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "FirstButton2D");
		static AQ_GameObject* background = gameObjectCtrl->getGameObject("Background");
		static AQ_CompSimpleBox2D* background2D = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(background, "Background2D");

		static bool mouseLeftOnPress{ false };

		double mouseXPos, mouseYPos;
		glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
		firstButton->hoverCheck(mouseXPos, mouseYPos, false);

		switch (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
		case GLFW_PRESS:
			if (!mouseLeftOnPress) {
				std::cout << "Mouse pressed\n";
				static std::string bckgroundTexNames[2]{ "TreeElfBackground", "Background2DTex" };
				static int currentIndex{ 0 };

				bool pressSuccess = firstButton->clickCheck(mouseXPos, mouseYPos, false);
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

	void firstButtonPredrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
}