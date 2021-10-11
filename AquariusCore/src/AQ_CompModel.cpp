#include "headers/AQ_CompModel.h"

AQ_CompModel::AQ_CompModel(unsigned int keyToModel) {
	this->pointerToDatabaseModel = &(AQ_Database::Models::allModels.at(keyToModel));
}