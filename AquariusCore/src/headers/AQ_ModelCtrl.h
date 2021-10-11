#pragma once
#include "AQ_Model.h"
#include <type_traits>
#include <iostream>

class AQ_ModelCtrl {
public:
	template<typename T>
	static void importModel(T* model, unsigned int& returnsKeyToModel) {
		if constexpr (std::is_base_of<AQ_Model, T>::value) {
			AQ_Database::Models::allModels.push_back(*model);
			returnsKeyToModel = AQ_Database::Models::allModels.size() - 1;
		} else {
			std::cout << "ERROR: IMPORTED OBJECT ISN'T A MODEL." << "\n";
		}
	}
};