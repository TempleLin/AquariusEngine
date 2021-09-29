#include "headers/AQ_GameObject.h"
#include "headers/AQ_GameObjectCtrl.h"

AQ_GameObject::~AQ_GameObject() {
	AQ_GameObjectCtrl::removeAllCompsOfGameObject(*this);
}