#pragma once
#include "AQ_GameObject.h"
#include "AQ_CompModel.h"
#include "AQ_CompCamera.h"
#include "AQ_Database.h"
#include "AQ_Component.h"

class AQ_GameObjectCtrl {
public:
	static void addCameraComponent(AQ_GameObject& gameObject, AQ_CompCamera camera) {
		AQ_DataBase::Components::addCameraComponent(camera, camera.dataBaseAcessKey);
		gameObject.components.push_back(camera);
	}
	static void addModelComponent(AQ_GameObject& gameObject, AQ_CompModel model) {
		AQ_DataBase::Components::addModelComponent(model, model.dataBaseAcessKey);
		gameObject.components.push_back(model);
	}
	static AQ_CompCamera& getCameraComponent(AQ_GameObject& gameObject, unsigned int index) {
		for (auto i : gameObject.components) {
			if (i.componentType == AQ_EComponents::CAMERA) {
				if (index) index--;
				else {
					return AQ_DataBase::Components::getCameraComponent(i.dataBaseAcessKey);
				}
			}
		}
	}
	static AQ_CompModel& getModelComponent(AQ_GameObject& gameObject, unsigned int index) {
		for (auto i : gameObject.components) {
			if (i.componentType == AQ_EComponents::MODEL) {
				if (index) index--;
				else {
					return AQ_DataBase::Components::getModelComponent(i.dataBaseAcessKey);
				}
			}
		}
	}
};