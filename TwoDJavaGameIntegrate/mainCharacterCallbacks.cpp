#include "headers/mainCharacterCallbacks.hpp"
#include "headers/TwoDJavaGameIntegrate.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <headers/AQ_Component.hpp>
#include <headers/AQ_CompSimpleBox2D.hpp>

/*
* @TODO:
*  1. Carefully think through how to implement references to other gameObjects when callbacks start/update.
*  2. Check all gameObjects' start/update functions of whether or not they're nullptr. If not, call them from gameObjectCtrl.
*  3. add stop() method to every gameObject which gets called from gameObjectCtrl when calls deleteGameObject().
*	  Can then delete references' arrays created from start/update.
*  4. Create method that retreives references created from start/update.
*  5. Try if const pointer can or cannot be reassigned. If can't, set some of the args as const.
*  6. Add layers (like Photoshop) to drawing methods. And use a value size sorting algorithm to sort layers and draw by layers.
*/

namespace mainCharacter {
	void mainCharacterPreDrawCallback(unsigned int shaderID, unsigned int* uniforms, AQ_CompSimpleBox2D* simpleBox2DThis);

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		gameObjectThis->setComponentsRefs(new AQ_Component * [1]{ gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "MainCharacter2D") });
		AQ_CompSimpleBox2D* mainChar2DComp = static_cast<AQ_CompSimpleBox2D*>(gameObjectThis->getComponentsRefs()[0]);

		int firstTextureIndex{ 0 };
		mainChar2DComp->addTexture("assets/cleanCharacter.png", "CleanCharacter", true, true, &firstTextureIndex);
		std::cout << "firstTextureIndex: " << firstTextureIndex << "\n";

		mainChar2DComp->setTexWrapFilter(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
		gameObjectThis->setOtherRefs(new void* [1]{ static_cast<void*>(new AQ_Shader("assets/shaders/two_d_tex_vs.glsl", "assets/shaders/two_d_tex_fs.glsl"))});
		std::cout << "Shader ID at main character: " << static_cast<AQ_Shader*>(gameObjectThis->getOtherRefs()[0])->ID << "\n";
		mainChar2DComp->setShaderID(static_cast<AQ_Shader*>(gameObjectThis->getOtherRefs()[0])->ID);
		mainChar2DComp->setUniforms(new const char* [4]{ "windowWidth", "windowHeight", "keepAspectRatio", "offsetMat" }, 4);
		mainChar2DComp->setPreDrawCallback(mainCharacterPreDrawCallback);
		mainChar2DComp->activateTexture(GL_TEXTURE0);
	}

	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis){
		static_cast<AQ_CompSimpleBox2D*>(gameObjectThis->getComponentsRefs()[0])->draw();
	}

	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		delete[] gameObjectThis->getComponentsRefs();
		delete static_cast<AQ_Shader*>(gameObjectThis->getOtherRefs()[0]);
		delete[] gameObjectThis->getOtherRefs();
	}


	void mainCharacterPreDrawCallback(unsigned int shaderID, unsigned int* uniforms, AQ_CompSimpleBox2D* simpleBox2DThis) {
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
		offsetMatrix = glm::translate(offsetMatrix, glm::vec3(-.5f, 0.f, 0.f));
		glUniformMatrix4fv(uniforms[3], 1, false, &offsetMatrix[0][0]);
	}

}