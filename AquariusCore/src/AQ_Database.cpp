#include "headers/AQ_Database.h"

class AQ_Database::Components;
class AQ_Database::GlobalLights;

unsigned int AQ_Database::Components::currentKeyIndex = 1;
std::map<unsigned int, AQ_CompModel> AQ_Database::Components::modelComponents;
std::map<unsigned int, AQ_CompCamera> AQ_Database::Components::cameraComponents;

std::vector<AQ_DirLight> AQ_Database::GlobalLights::directionalLights;
std::vector<AQ_PointLight> AQ_Database::GlobalLights::pointLights;
std::vector<AQ_SpotLight> AQ_Database::GlobalLights::spotLights;