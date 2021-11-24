#include "headers/mainCharacterCallbacks.hpp"
#include "headers/TwoDJavaGameIntegrate.hpp"
#include "headers/PassingValues.hpp"
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
	void mainCharacterPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		AQ_CompSimpleBox2D* mainChar2DComp = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "MainCharacter2D");

		int firstTextureIndex{ 0 };
		mainChar2DComp->addDiffuseTexture("assets/cleanCharacter.png", "CleanCharacter", true,
			GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, &firstTextureIndex);

		mainChar2DComp->setAnimSprites(std::vector<std::string>{
			"assets/Animations/MainCharWalk/1.png",
			"assets/Animations/MainCharWalk/2.png",
			"assets/Animations/MainCharWalk/3.png",
			"assets/Animations/MainCharWalk/4.png",
			"assets/Animations/MainCharWalk/5.png",
			"assets/Animations/MainCharWalk/6.png",
			"assets/Animations/MainCharWalk/7.png",
			"assets/Animations/MainCharWalk/8.png",
			"assets/Animations/MainCharWalk/9.png",
			"assets/Animations/MainCharWalk/10.png",
			"assets/Animations/MainCharWalk/11.png",
		}, GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true);

		mainChar2DComp->setPreDrawCallback(mainCharacterPreDrawCallback);

		gameObjectThis->transformTranslate(glm::vec3(0.f, .1f, 0.f));
	}

	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis){
		if (currentScene == CurrentScene::MAINHALL) {
			static AQ_GlobalCtrl::TimeCtrl* timeCtrl = gameObjectCtrl->getUniControls()->getGlobalCtrl()->getTimeCtrl();
			static AQ_CompSimpleBox2D* mainChar2DComp = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "MainCharacter2D");
			//mainChar2DComp->draw();
			mainChar2DComp->drawSpriteAnim(timeCtrl->getSecondsInGame());
		}
	}

	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}

	void mainCharacterPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {
		if (currentScene == CurrentScene::MAINHALL) {
			simpleBox2DThis->transformReset();
			simpleBox2DThis->transformTranslate(glm::vec3(-.45f, 0.f, 0.f));
			simpleBox2DThis->transformScale(glm::vec3(2.f, 2.f, 1.f));
		}
	}
}