#include "headers/attackCallbacks.h"
#include "headers/PassingValues.hpp"
#include "headers/CustomButtonComp.hpp"
#include "headers/charactersStats.hpp"
#include <headers/AQ_CompSimpleBox2D.hpp>

namespace attack {
	void selectionPagePreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);
	void monster0BtnPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);
	void monster1BtnPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);
	void succubusPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);

	void startSelectionPageComps();
	void startAttackingComps();

	void mainCharFightMobs(AQ_GameObjectCtrl* gameObjectCtrl, int enemiesCount, CharacterStats** enemies);

	enum class AttackMode {
		SELECTING,
		ATTACKING0,
		ATTACKING1
	};
	AttackMode attackMode = AttackMode::SELECTING;

	AQ_CompSimpleBox2D* attackSelectionPage;
	CustomButtonComp* selectionMonsterBtn0;
	CustomButtonComp* selectionMonsterBtn1;
	AQ_CompSimpleBox2D* succubus;

	AQ_GameObject* mainCharacterObject;
	AQ_CompSimpleBox2D* mainChar2D;

	void start(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		attackSelectionPage = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "AttackSelectionPage");
		selectionMonsterBtn0 = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "SelectionMonsterBtn0");
		selectionMonsterBtn1 = gameObjectCtrl->getComponent<CustomButtonComp>(gameObjectThis, "SelectionMonsterBtn1");
		succubus = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(gameObjectThis, "Succubus2D");

		mainCharacterObject = gameObjectCtrl->getGameObject("MainCharacter");
		mainChar2D = gameObjectCtrl->getComponent<AQ_CompSimpleBox2D>(mainCharacterObject, "MainCharacter2D");

		startSelectionPageComps();
		startAttackingComps();
	}
	void update(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis) {
		static AQ_GlobalCtrl::TimeCtrl* timeCtrl = gameObjectCtrl->getUniControls()->getGlobalCtrl()->getTimeCtrl();

		if (currentScene == CurrentScene::ATTACK) {
			switch (attackMode) {
			case AttackMode::SELECTING:
				attackSelectionPage->draw();
				selectionMonsterBtn0->draw();
				selectionMonsterBtn1->draw();
				break;
			case AttackMode::ATTACKING1:
				succubus->transformTranslate(glm::vec3(glm::sin(timeCtrl->getSecondsInGame()) * .001f, glm::cos(timeCtrl->getSecondsInGame()) * .001f, 0.f));
				succubus->draw();

				mainChar2D->transformScale(glm::vec3(-1.f, 1.f, 1.f));
				mainChar2D->drawSpriteAnim(timeCtrl->getSecondsInGame());
				mainChar2D->transformScale(glm::vec3(-1.f, 1.f, 1.f));

				mainCharFightMobs(gameObjectCtrl, 1, new CharacterStats* { &succubusStats });
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
							attackMode = AttackMode::ATTACKING0;
						} else if (onClickMonstersBtns[1]) {
							std::cout << "Pressed second monster button\n";
							attackMode = AttackMode::ATTACKING1;
						}
						mouseLeftOnPress = true;
					}
					break;
				case GLFW_RELEASE:
					mouseLeftOnPress = false;
					break;
				}
				break;
			case AttackMode::ATTACKING0:
				break;
			case AttackMode::ATTACKING1:
				break;
			}
		}
	}

	void mainCharFightMobs(AQ_GameObjectCtrl* gameObjectCtrl, int enemiesCount, CharacterStats** enemies = nullptr) {
		static AQ_GlobalCtrl::TimeCtrl* timeCtrl = gameObjectCtrl->getUniControls()->getGlobalCtrl()->getTimeCtrl();
		static CharacterStats** _enemies{ nullptr };
		if (enemies) {
			if (_enemies)
				delete[] _enemies;
			_enemies = enemies;
		}
		if (!_enemies) {
			std::cout << "No enemies passed in fighting, cancelled fight.\n";
			return;
		}

		bool allEnemiesDead{ false };
		static bool mainCharTurnToAttack{ true };

		static float lastGameTime{ 0.f };
		if (timeCtrl->getSecondsInGame() - lastGameTime >= .2f) {
			switch (mainCharTurnToAttack) {
			case true:
				for (int i = 0; i < enemiesCount; i++) {
					if (!_enemies[i]->isDead()) {
						_enemies[i]->receiveAttack(mainCharStats);
						break; // Attack single enemy at a time.
					}
					if (i == enemiesCount - 1 && _enemies[i]->isDead()) {
						allEnemiesDead = true;
					}
				}
				mainCharTurnToAttack = false;
				break;
			case false:
				for (int i = 0; i < enemiesCount; i++) {
					mainCharStats.receiveAttack(succubusStats);
				}
				mainCharTurnToAttack = true;
				break;
			}
			lastGameTime = timeCtrl->getSecondsInGame();
		}
		if (mainCharStats.isDead()) {
			currentScene = CurrentScene::MAINHALL;
		} else if (allEnemiesDead) {
			delete[] _enemies;
			currentScene = CurrentScene::MAINHALL;
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
		succubus->addDiffuseTexture("assets/Succubus.png", "SuccubusImageTex", GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR, true, &returnTexIndex);
		succubus->transformTranslate(glm::vec3(.5f, 0.f, 0.f));
		succubus->transformScale(glm::vec3(1.f, 2.3f, 1.f));
		succubus->setPreDrawCallback(succubusPreDrawCallback);
	}

	void selectionPagePreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
	void monster0BtnPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
	void monster1BtnPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
	void succubusPreDrawCallback(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis) {

	}
}