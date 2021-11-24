#include "headers/attackCallbacks.h"
#include "headers/PassingValues.hpp"
#include "headers/CustomButtonComp.hpp"
#include <headers/AQ_CompSimpleBox2D.hpp>

namespace attack {
	void selectionPagePreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);
	void monster0BtnPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);
	void monster1BtnPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);
	void treeMonsterPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);

	void startSelectionPageComps();
	void startAttackingComps();

	enum class AttackMode {
		SELECTING,
		ATTACKING
	};
	AttackMode attackMode = AttackMode::SELECTING;

	AQ_CompSimpleBox2D* attackSelectionPage;
	CustomButtonComp* selectionMonsterBtn0;
	CustomButtonComp* selectionMonsterBtn1;
	AQ_CompSimpleBox2D* treeMonster;

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		attackSelectionPage = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "AttackSelectionPage");
		selectionMonsterBtn0 = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "SelectionMonsterBtn0");
		selectionMonsterBtn1 = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "SelectionMonsterBtn1");
		treeMonster = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "TreeMonster");

		startSelectionPageComps();
		startAttackingComps();
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
				treeMonster->draw();
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

		if (currentScene == CurrentScene::ATTACK) {
			static bool monstersBtnExpand[]{ true, true };
			bool onHoverMonstersBtns[] = {
				selectionMonsterBtn0->hoverCheck(mouseXPos, mouseYPos, false),
				selectionMonsterBtn1->hoverCheck(mouseXPos, mouseYPos, false)
			};

			static bool mouseLeftOnPress{ false };

			switch (attackMode) {
			case AttackMode::SELECTING:
				if (onHoverMonstersBtns[0] && monstersBtnExpand[0]) {
					selectionMonsterBtn0->transformScale(glm::vec3(1.2f, 1.2f, 1.f));
					monstersBtnExpand[0] = false;
				} else if (!onHoverMonstersBtns[0] && !monstersBtnExpand[0]) {
					selectionMonsterBtn0->transformScale(glm::vec3(1.f / 1.2f, 1.f / 1.2f, 1.f));
					monstersBtnExpand[0] = true;
				} else if (onHoverMonstersBtns[1] && monstersBtnExpand[1]) {
					selectionMonsterBtn1->transformScale(glm::vec3(1.2f, 1.2f, 1.f));
					monstersBtnExpand[1] = false;
				} else if (!onHoverMonstersBtns[1] && !monstersBtnExpand[1]) {
					selectionMonsterBtn1->transformScale(glm::vec3(1.f / 1.2f, 1.f / 1.2f, 1.f));
					monstersBtnExpand[1] = true;
				}

				switch (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
				case GLFW_PRESS:
					if (!mouseLeftOnPress) {
						bool onClickMonstersBtns[] = {
							selectionMonsterBtn0->clickCheck(mouseXPos, mouseYPos, false),
							selectionMonsterBtn1->clickCheck(mouseXPos, mouseYPos, false)
						};

						if (onClickMonstersBtns[0]) {
							std::cout << "Pressed first monster button\n";
							attackMode = AttackMode::ATTACKING;

						} else if (onClickMonstersBtns[1]) {
							std::cout << "Pressed second monster button\n";
						}
						mouseLeftOnPress = true;
					}
					break;
				case GLFW_RELEASE:
					mouseLeftOnPress = false;
					break;
				}

				break;
			case AttackMode::ATTACKING:
				break;
			}
		}
	}

	void startSelectionPageComps() {
		int returnTexIndex{};
		attackSelectionPage->addDiffuseTexture("assets/AttackSelectionPage.png", "AttackSelectionPageImageTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR,
			true, &returnTexIndex);
		attackSelectionPage->setPreDrawCallback(selectionPagePreDrawCallback);

		selectionMonsterBtn0->addDiffuseTexture("assets/SelectionMonster0.png", "Monster0DiffuseTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &returnTexIndex);
		glm::vec3 topLeft{ -0.5f,  0.5f, .0f };
		glm::vec3 topRight{ 0.5f,  0.5f, .0f };
		glm::vec3 bottomRight{ 0.5f, -0.5f, .0f };
		glm::vec3 bottomLeft{ -0.5f, -0.5f, .0f };
		selectionMonsterBtn0->setSensorRange(topLeft, topRight, bottomRight, bottomLeft);
		selectionMonsterBtn0->keepAspectRatio();
		selectionMonsterBtn0->setPreDrawCallback(monster0BtnPreDrawCallback);
		selectionMonsterBtn0->transformTranslate(glm::vec3(-.1f, .4f, 0.f));
		selectionMonsterBtn0->translateSensorRange(glm::vec3(-.1f, .4f, 0.f));
		selectionMonsterBtn0->transformScale(glm::vec3(.6f, .6f, 1.f));
		selectionMonsterBtn0->scaleSensorRange(glm::vec3(.6f, .6f, 1.f));

		selectionMonsterBtn1->addDiffuseTexture("assets/SelectionMonster1.png", "Monster1DiffuseTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &returnTexIndex);
		selectionMonsterBtn1->setSensorRange(topLeft, topRight, bottomRight, bottomLeft);
		selectionMonsterBtn1->keepAspectRatio();
		selectionMonsterBtn1->setPreDrawCallback(monster1BtnPreDrawCallback);
		selectionMonsterBtn1->transformTranslate(glm::vec3(.5f, -.4f, 0.f));
		selectionMonsterBtn1->translateSensorRange(glm::vec3(.5f, -.4f, 0.f));
		selectionMonsterBtn1->transformScale(glm::vec3(.6f, .6f, 1.f));
		selectionMonsterBtn1->scaleSensorRange(glm::vec3(.6f, .6f, 1.f));
	}
	void startAttackingComps() {
		int returnTexIndex{};
		treeMonster->addDiffuseTexture("assets/TreeMonster.png", "TreeMonsterImageTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &returnTexIndex);
		treeMonster->setPreDrawCallback(treeMonsterPreDrawCallback);
	}

	void selectionPagePreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
	void monster0BtnPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
	void monster1BtnPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
	void treeMonsterPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
}