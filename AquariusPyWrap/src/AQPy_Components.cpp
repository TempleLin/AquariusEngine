#include <string>

#include "headers/AQPy_Components.h"
#include <headers/AQ_CompCamera.h>
#include <headers/AQ_CompModel.h>
#include <headers/AQ_GameObjectCtrl.h>

extern "C" {
	const char* cameraComponentName = typeid(AQ_CompCamera).name();
	const char* modelComponentName = typeid(AQ_CompModel).name();

	AQ_CompCamera* createCompCamera(float posX = 0.f, float posY = 0.f, float posZ = 0.f, float frontX = 0.f, float frontY = 0.f, float frontZ = -1.f,
		float worldUpX = 0.f, float worldUpY = 1.f, float worldUpZ = 0.f,
		float yaw = YAW, float pitch = PITCH, float movementSpeed = SPEED, float mouseSensitivity = SENSITIVITY, float zoom = ZOOM) {
		return new AQ_CompCamera(glm::vec3(posX, posY, posZ), glm::vec3(frontX, frontY, frontZ), 
			glm::vec3(worldUpX, worldUpY, worldUpZ), yaw, pitch, movementSpeed, mouseSensitivity, zoom);
	}

	void addComponentToGameObject(AQ_GameObject* gameobject, char* compName) {
		if (compName == cameraComponentName) {
			AQ_AddComponent<AQ_CompCamera>(*gameobject, )
		}
	}
}