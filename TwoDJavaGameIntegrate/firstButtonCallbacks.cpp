#include "headers/firstButtonCallbacks.hpp"
#include <headers/AQ_CompBoxButton2D.hpp>
#include <headers/AQ_GlobalCtrl.hpp>
#include "headers/glConfigCallbacks.h"

namespace firstButton {
	void firstButtonPredrawCallback(unsigned int shaderID, unsigned int* uniforms, AQ_CompSimpleBox2D* simpleBox2DThis);

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		AQ_CompBoxButton2D* firstBtn2D = gameObjectCtrl->getComponent<AQ_CompBoxButton2D>(gameObjectThis, "FirstButton2D");
		AQ_GameObject* mainCharacterGameObject{};
		mainCharacterGameObject = gameObjectCtrl->getGameObject("MainCharacter");

		float topLeft[3]{ -0.5f,  0.5f, .0f };
		float topRight[3]{ 0.5f,  0.5f, .0f };
		float bottomRight[3]{ 0.5f, -0.5f, .0f };
		float bottomLeft[3]{ -0.5f,  -0.5f, .0f };
		firstBtn2D->setSensorRange(topLeft, topRight, bottomRight, bottomLeft);
		std::cout << "Shader ID at first button: " << static_cast<AQ_Shader*>(mainCharacterGameObject->getOtherRefs()[0])->ID << "\n";
		firstBtn2D->setShaderID((static_cast<AQ_Shader*>(mainCharacterGameObject->getOtherRefs()[0]))->ID);
		int firstButtonTextIndex{};
		firstBtn2D->addTexture("assets/tempButton.png", "FirstButton2D", true, true, &firstButtonTextIndex);
		firstBtn2D->setUniforms(new const char* [4]{ "windowWidth", "windowHeight", "keepAspectRatio", "offsetMat" }, 4);
		firstBtn2D->keepAspectRatio();
		firstBtn2D->setPreDrawCallback(firstButtonPredrawCallback);
		firstBtn2D->activateTexture(GL_TEXTURE0);
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
		if (glfwGetKey(window, keys[0]) == actions[0]) {
			std::cout << "Key pressed\n";
			firstButton->clickCheck(MousePosCallback::getXPos(), MousePosCallback::getYPos(), false);
		}
	}

	void firstButtonPredrawCallback(unsigned int shaderID, unsigned int* uniforms, AQ_CompSimpleBox2D* simpleBox2DThis) {
		glUseProgram(shaderID);
		static GLFWwindow* currentWindow = simpleBox2DThis->getGameObject()->getGameObjectCtrl()->getSceneGameObjects()
			->getScene()->getCurrentWindow();
		int windowWidth, windowHeight;
		glfwGetWindowSize(currentWindow, &windowWidth, &windowHeight);
		simpleBox2DThis->bindTexture(0);
		glm::mat4 offsetMatrix(1.f);
		offsetMatrix = glm::translate(offsetMatrix, glm::vec3(-.5f, 0.f, 0.f));
		glUniformMatrix4fv(uniforms[3], 1, false, &offsetMatrix[0][0]);
	}
}