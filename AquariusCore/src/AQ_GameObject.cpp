#include "headers/AQ_GameObject.h"
#include "headers/AQ_GameObjectCtrl.h"

AQ_GameObject::~AQ_GameObject() {
	static int gameObjectsDeletedCount{ 1 };
	std::cout << "Gameobject deleted count: " << gameObjectsDeletedCount << "\n";
	AQ_GameObjectCtrl::removeAllCompsOfGameObject(*this);
}