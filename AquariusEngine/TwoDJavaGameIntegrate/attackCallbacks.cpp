#include "headers/attackCallbacks.h"
#include "headers/PassingValues.hpp"
#include "headers/CustomButtonComp.hpp"
#include <headers/AQ_CompSimpleBox2D.hpp>

namespace attack {
	void selectionPagePreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);
	void monster0BtnPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);
	void monster1BtnPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);

	enum class AttackMode {
		SELECTING,
		ATTACKING
	};
	AttackMode attackMode = AttackMode::SELECTING;

	AQ_CompSimpleBox2D* attackSelectionPage;
	CustomButtonComp* selectionMonsterBtn0;
	CustomButtonComp* selectionMonsterBtn1;

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		attackSelectionPage = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "AttackSelectionPage");
		selectionMonsterBtn0 = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "SelectionMonsterBtn0");
		selectionMonsterBtn1 = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "SelectionMonsterBtn1");

		int returnTexIndex{};
		attackSelectionPage->addDiffuseTexture("assets/AttackSelectionPage.png", "AttackSelectionPageImageTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
			true, &returnTexIndex);
		attackSelectionPage->activateTexture(GL_TEXTURE0);
		attackSelectionPage->setShaderID(shaders.at(0).ID);
		attackSelectionPage->setPreDrawCallback(selectionPagePreDrawCallback);

		selectionMonsterBtn0->addDiffuseTexture("assets/SelectionMonster0.png", "Monster0DiffuseTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &returnTexIndex);
		glm::vec3 topLeft{ -0.5f,  0.5f, .0f };
		glm::vec3 topRight{ 0.5f,  0.5f, .0f };
		glm::vec3 bottomRight{ 0.5f, -0.5f, .0f };
		glm::vec3 bottomLeft{ -0.5f, -0.5f, .0f };
		selectionMonsterBtn0->setSensorRange(topLeft, topRight, bottomRight, bottomLeft);
		selectionMonsterBtn0->activateTexture(GL_TEXTURE0);
		selectionMonsterBtn0->setShaderID(shaders.at(0).ID);
		selectionMonsterBtn0->keepAspectRatio();
		selectionMonsterBtn0->setPreDrawCallback(monster0BtnPreDrawCallback);
		selectionMonsterBtn0->transformTranslate(glm::vec3(-.1f, .4f, 0.f));
		selectionMonsterBtn0->translateSensorRange(glm::vec3(-.1f, .4f, 0.f));
		selectionMonsterBtn0->transformScale(glm::vec3(.6f, .6f, 1.f));
		selectionMonsterBtn0->scaleSensorRange(glm::vec3(.6f, .6f, 1.f));

		selectionMonsterBtn1->addDiffuseTexture("assets/SelectionMonster1.png", "Monster1DiffuseTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &returnTexIndex);
		selectionMonsterBtn1->setSensorRange(topLeft, topRight, bottomRight, bottomLeft);
		selectionMonsterBtn1->activateTexture(GL_TEXTURE0);
		selectionMonsterBtn1->setShaderID(shaders.at(0).ID);
		selectionMonsterBtn1->keepAspectRatio();
		selectionMonsterBtn1->setPreDrawCallback(monster1BtnPreDrawCallback);
		selectionMonsterBtn1->transformTranslate(glm::vec3(.5f, -.4f, 0.f));
		selectionMonsterBtn1->translateSensorRange(glm::vec3(.5f, -.4f, 0.f));
		selectionMonsterBtn1->transformScale(glm::vec3(.6f, .6f, 1.f));
		selectionMonsterBtn1->scaleSensorRange(glm::vec3(.6f, .6f, 1.f));
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		if (currentScene == CurrentScene::ATTACK) {
			switch (attackMode) {
			case AttackMode::SELECTING:
				attackSelectionPage->draw();
				selectionMonsterBtn0->draw();
				selectionMonsterBtn1->draw();
				break;
			case AttackMode::ATTACKING:

				break;
			}
		}
	}
	void stop(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {

	}
	void processInputs(GLFWwindow* window, AQ_GameObject* gameObjectThis, AQ_GlobalCtrl::TimeCtrl* timeCtrl,
		unsigned int* keys, unsigned int* actions) {

		static bool mouseLeftOnPress{ false };
		double mouseXPos, mouseYPos;
		glfwGetCursorPos(window, &mouseXPos, &mouseYPos);

		static bool monster0BtnExpand{ true };
		bool onHoverMonster0 = selectionMonsterBtn0->hoverCheck(mouseXPos, mouseYPos, false);
		if (onHoverMonster0 && monster0BtnExpand) {
			selectionMonsterBtn0->transformScale(glm::vec3(1.2f, 1.2f, 1.f));
			monster0BtnExpand = false;
		} else if (!onHoverMonster0 && !monster0BtnExpand) {
			selectionMonsterBtn0->transformScale(glm::vec3(1.f / 1.2f, 1.f / 1.2f, 1.f));
			monster0BtnExpand = true;
		}
	}

	void selectionPagePreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
	void monster0BtnPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
	void monster1BtnPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
}