#pragma once
#include "AQ_GameObject.h"
#include "AQ_CompModel.h"
#include "AQ_CompCamera.h"
#include "AQ_Database.h"
#include "AQ_Component.h"
#include <iostream>
#include <type_traits>

class AQ_GameObjectCtrl {
public:
	static void addCameraComponent(AQ_GameObject& gameObject, AQ_CompCamera camera);
	static void addModelComponent(AQ_GameObject& gameObject, AQ_CompModel model);

	static AQ_CompCamera& getCameraComponent(AQ_GameObject& gameObject, unsigned int index);
	static AQ_CompModel& getModelComponent(AQ_GameObject& gameObject, unsigned int index);
};