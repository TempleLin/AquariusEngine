#include "headers/AQ_Database.h"

unsigned int AQ_Database::Components::currentKeyIndex = 1;

std::vector<AQ_DirLight> AQ_Database::GlobalLights::directionalLights;
std::vector<AQ_PointLight> AQ_Database::GlobalLights::pointLights;
std::vector<AQ_SpotLight> AQ_Database::GlobalLights::spotLights;

std::vector<AQ_Model> AQ_Database::Models::allModels;