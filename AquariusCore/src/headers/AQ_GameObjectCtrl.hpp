#pragma once
#include "AQ_GameObject.hpp"
#include "AQ_CompModel.hpp"
#include "AQ_CompCamera.hpp"
#include "AQ_Database.hpp"
#include "AQ_Component.hpp"
#include <string>
#include <iostream>
#include <type_traits>
#include <utility>

namespace aquarius_engine {
	/*
	* @Reminder:
	*	1.A gameobject can have components with same name only when they each are different types.
	*/

	class AQ_GameObjectCtrl {
		friend class AQ_GameObject;
	private:
		AQ_Scene::GameObjects::Components* sceneComponents;
		AQ_Scene::GameObjects* sceneGameObjects;
		unsigned int getComponentIndex(const std::vector<std::pair<std::string, unsigned int>>& compVector,
			std::string& nameOfComponent);
	public:
		AQ_GameObjectCtrl(AQ_Scene::GameObjects::Components* databaseComponent, AQ_Scene::GameObjects* databaseGameObjects);

		AQ_GameObject* createGameObject(std::string name);
		AQ_GameObject* getGameObject(std::string name);

		void deleteGameObject(std::string name);

		void startGameObjects();
		void updateGameObjects();
		void stopGameObjects();

		template <typename T, typename = std::enable_if_t<std::is_base_of<AQ_Component, T>::value>>
		T* addComponent(AQ_GameObject* gameObject, T* component, std::string name) {
			try {
				component->name = name;
				/*
				* @Add the component with to the database and receive its key in database by returning in to
				*  component object's databaseAccessKey.
				*/
				sceneComponents->addComponent(static_cast<void*>(component), component->databaseAccessKey);
				const auto& componentsKeysVecRef = gameObject->componentsKeys[typeid(T)];
				// @Check if the name specified already exists in the gameobject's components.
				for (int i = 0; i < componentsKeysVecRef.size(); i++) {
					if (componentsKeysVecRef.at(i).first == name) {
						throw std::string("ERROR: GAMEOBJECT'S SAME COMPONENT TYPE ALREADY HAS ONE WITH THE NAME");
					}
				}
				// @Save name and access key to database descriptions of the component to the gameobject.
				gameObject->componentsKeys[typeid(T)].push_back(std::pair<std::string, unsigned int>(name, component->databaseAccessKey));
				component->gameObjectThis = gameObject;
				component->gameObjectTrans = gameObject->transform;
				component->transformOffset = glm::mat4(1.f);
				return component;
			} catch (std::string& errorMessage) {
				std::cout << errorMessage << "\n";
				return nullptr;
			} catch (std::out_of_range& e) {
				std::cout << "ERROR: CANNOT ADD COMPONENT FROM GAMEOBJECT" << e.what() << "\n";
				return nullptr;
			} catch (...) {
				std::cout << "ERROR: UNKNOW ERROR IN ADDCOMPONENT FROM AQ_GAMEOBJECTCTRL" << "\n";
				return nullptr;
			}
		}

		template <typename T, typename = std::enable_if_t<std::is_base_of<AQ_Component, T>::value>>
		T* getComponent(AQ_GameObject* gameObject, std::string name) {
			try {
				const auto& componentsKeysVecRef = gameObject->componentsKeys[typeid(T)];
				return static_cast<T*>(sceneComponents->allComponents
					.at(componentsKeysVecRef.at(getComponentIndex(componentsKeysVecRef, name)).second));
			} catch (std::out_of_range& e) {
				std::cout << "FAILED TO GET COMPONENT FROM GAMEOBJECT CTRL" << e.what() << "\n";
				return nullptr;
			} catch (...) {
				std::cout << "ERROR: UNKNOW ERROR FROM GETTING COMPONENT IN AQ_GAMEOBJECTCTRL" << "\n";
				return nullptr;
			}
		}

		template <typename T, typename = std::enable_if_t<std::is_base_of<AQ_Component, T>::value>>
		void removeComponent(AQ_GameObject* gameObject, std::string name) {
			try {
				const auto& componentsKeysVecRef = gameObject->componentsKeys[typeid(T)];
				sceneComponents->allComponents.erase
					(componentsKeysVecRef.at(getComponentIndex(componentsKeysVecRef, name)).second);
			} catch (std::out_of_range& e) {
				std::cout << "FAILED TO REMOVE COMPONENT FROM GAMEOBJECT CTRL" << e.what() << "\n";
			} catch (...) {
				std::cout << "ERROR: UNKNOW ERROR FROM REMOVING COMPONENT IN AQ_GAMEOBJECTCTRL" << "\n";
			}
		}

		void removeAllCompsOfGameObject(AQ_GameObject* gameObject);
	};
}