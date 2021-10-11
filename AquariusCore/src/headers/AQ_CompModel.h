#pragma once
#include "AQ_Component.h"
#include "AQ_Model.h"
#include "AQ_Database.h"

class AQ_CompModel {
	AQ_Model* pointerToDatabaseModel;
	AQ_CompModel(unsigned int keyToModel);
};