#include "headers/AQ_Database.h"

class AQ_DataBase::Components;
class AQ_DataBase::GlobalLights;

unsigned int AQ_DataBase::Components::currentKeyIndex = 1;
std::map<unsigned int, AQ_CompModel> AQ_DataBase::Components::modelComponents;
std::map<unsigned int, AQ_CompCamera> AQ_DataBase::Components::cameraComponents;

std::vector<AQ_DirLight> AQ_DataBase::GlobalLights::directionalLights;
std::vector<AQ_PointLight> AQ_DataBase::GlobalLights::pointLights;
std::vector<AQ_SpotLight> AQ_DataBase::GlobalLights::spotLights;