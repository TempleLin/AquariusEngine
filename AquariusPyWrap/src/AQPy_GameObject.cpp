#include <headers/AQ_GameObject.h>

extern "C" {
	AQ_GameObject* createGameObject() {
		return new AQ_GameObject();
	}
}