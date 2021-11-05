#include "headers/backgroundCallbacks.h"
#include "headers/PassingValues.hpp"
#include <headers/AQ_CompSimpleBox2D.hpp>

namespace background_callbacks {
	void backgroundPreDrawCallback(unsigned int shaderID, unsigned int* uniforms, AQ_CompSimpleBox2D* simpleBox2DThis);

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		AQ_CompSimpleBox2D* background2D = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "Background2D");
		int returnTexIndex{};
		background2D->addTexture("assets/background.png", "Background2DTex", true, true, &returnTexIndex);
		background2D->setTexWrapFilter(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
		background2D->activateTexture(GL_TEXTURE0);

		background2D->setShaderID(shaders.at(0).ID);
		background2D->setUniforms(new const char* [4]{ "windowWidth", "windowHeight", "keepAspectRatio", "offsetMat" }, 4);
		//background2D->keepAspectRatio();
		background2D->setPreDrawCallback(backgroundPreDrawCallback);
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		static AQ_CompSimpleBox2D* background2D = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "Background2D");
		background2D->draw();
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}

	void backgroundPreDrawCallback(unsigned int shaderID, unsigned int* uniforms, AQ_CompSimpleBox2D* simpleBox2DThis) {
		glUseProgram(shaderID);
		static GLFWwindow* currentWindow = simpleBox2DThis->getGameObject()->getGameObjectCtrl()->getSceneGameObjects()
			->getScene()->getCurrentWindow();
		int windowWidth, windowHeight;
		glfwGetWindowSize(currentWindow, &windowWidth, &windowHeight);
		/*glUniform1f(uniforms[0], (float)windowWidth);
		glUniform1f(uniforms[1], (float)windowHeight);
		glUniform1i(uniforms[2], GLFW_TRUE);*/
		simpleBox2DThis->bindTexture(0);
		glUniformMatrix4fv(uniforms[3], 1, false, &(simpleBox2DThis->getOffsetMatrix())[0][0]);
	}
}