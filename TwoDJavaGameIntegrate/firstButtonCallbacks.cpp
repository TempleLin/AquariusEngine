#include "headers/firstButtonCallbacks.hpp"
#include <headers/AQ_CompBoxButton2D.hpp>
#include <headers/AQ_GlobalCtrl.hpp>
#include <glm/glm.hpp>
#include "headers/glConfigCallbacks.hpp"

namespace firstButton {
	void firstButtonPredrawCallback(unsigned int shaderID, unsigned int* uniforms, AQ_CompSimpleBox2D* simpleBox2DThis);

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		AQ_CompBoxButton2D* firstBtn2D = gameObjectCtrl->getComponent<AQ_CompBoxButton2D>(gameObjectThis, "FirstButton2D");
		AQ_GameObject* mainCharacterGameObject{};
		mainCharacterGameObject = gameObjectCtrl->getGameObject("MainCharacter");

		int firstButtonTexIndex{};
		firstBtn2D->addTexture("assets/tempButton.png", "FirstButton2D", true, true, &firstButtonTexIndex);
		firstBtn2D->setTexWrapFilter(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
		glm::vec3 topLeft{ -0.5f,  0.5f, .0f };
		glm::vec3 topRight{ 0.5f,  0.5f, .0f };
		glm::vec3 bottomRight{ 0.5f, -0.5f, .0f };
		glm::vec3 bottomLeft{ -0.5f, -0.5f, .0f };
		firstBtn2D->setSensorRange(topLeft, topRight, bottomRight, bottomLeft);
		firstBtn2D->translateSensorRange(glm::vec3(.5f, 0.f, 0.f));
		firstBtn2D->scaleSensorRange(glm::vec3(1.f, .4f, 1.f));
		firstBtn2D->activateTexture(GL_TEXTURE0);
		firstBtn2D->setShaderID((static_cast<AQ_Shader*>(mainCharacterGameObject->getOtherRefs()[0]))->ID);
		firstBtn2D->setUniforms(new const char* [4]{ "windowWidth", "windowHeight", "keepAspectRatio", "offsetMat" }, 4);
		firstBtn2D->keepAspectRatio();
		firstBtn2D->setPreDrawCallback(firstButtonPredrawCallback);
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		static AQ_CompBoxButton2D* firstBtn2D = gameObjectCtrl->getComponent<AQ_CompBoxButton2D>(gameObjectThis, "FirstButton2D");
		firstBtn2D->draw();
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}

	void processInputs(GLFWwindow* window, AQ_GameObject* gameObjectThis, AQ_GlobalCtrl::TimeCtrl* timeCtrl,
		unsigned int* keys, unsigned int* actions) {
		AQ_CompBoxButton2D* firstButton = gameObjectThis->getGameObjectCtrl()->getComponent<AQ_CompBoxButton2D>(gameObjectThis, "FirstButton2D");
		//firstButton->hoverCheck(mouseXPos, mouseYPos, false);

		static bool mouseLeftOnPress{ false };

		switch (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
		case GLFW_PRESS:
			if (!mouseLeftOnPress) {
				std::cout << "Mouse pressed\n";
				double mouseXPos, mouseYPos;
				glfwGetCursorPos(window, &mouseXPos, &mouseYPos);
				firstButton->clickCheck(mouseXPos, mouseYPos, false);
				mouseLeftOnPress = true;
			}
			break;
		case GLFW_RELEASE:
			mouseLeftOnPress = false;
			break;
		}
	}

	void firstButtonPredrawCallback(unsigned int shaderID, unsigned int* uniforms, AQ_CompSimpleBox2D* simpleBox2DThis) {
		glUseProgram(shaderID);
		static GLFWwindow* currentWindow = simpleBox2DThis->getGameObject()->getGameObjectCtrl()->getSceneGameObjects()
			->getScene()->getCurrentWindow();
		int windowWidth, windowHeight;
		glfwGetWindowSize(currentWindow, &windowWidth, &windowHeight);
		glUniform1f(uniforms[0], (float)windowWidth);
		glUniform1f(uniforms[1], (float)windowHeight);
		glUniform1i(uniforms[2], GLFW_TRUE);
		simpleBox2DThis->bindTexture(0);
		glm::mat4 offsetMatrix(1.f);
		offsetMatrix = glm::translate(offsetMatrix, glm::vec3(.5f, 0.f, 0.f));
		offsetMatrix = glm::scale(offsetMatrix, glm::vec3(1.f, .4f, 1.f));
		glUniformMatrix4fv(uniforms[3], 1, false, &offsetMatrix[0][0]);
	}
}