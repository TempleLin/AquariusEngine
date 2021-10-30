#include "mainCharacterCallbacks.hpp"
#include <headers/AQ_Component.hpp>
#include <headers/AQ_CompSimple2D.hpp>

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
	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis, AQ_Component** components, void* otherRefs) {
		components = new AQ_Component * [1]{ gameObjectCtrl->getComponent<AQ_Component>(gameObjectThis, "MainCharacter2D") };
		AQ_CompSimple2D* mainChar2DComp = static_cast<AQ_CompSimple2D*>(components[0]);

		int firstTextureIndex{ 0 };
		mainChar2DComp->addTexture("assets/cleanCharacter.png", "CleanCharacter", true, true, &firstTextureIndex);
		mainChar2DComp->setTexWrapFilter(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);
		mainChar2DComp->setShaderID(twoDShader->ID);
		mainChar2DComp->setUniforms(new const char* [4]{ "windowWidth", "windowHeight", "keepAspectRatio", "offsetMat" }, 4);
		mainChar2DComp->setPreDrawCallback(mainCharacterPreDrawCallback);
		mainChar2DComp->activateTexture(GL_TEXTURE0);
	}

	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis, AQ_Component** components, void* otherRefs) {

	}
}