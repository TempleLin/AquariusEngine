#pragma once
#include <string>
#include <map>
#include <vector>
#include <type_traits>
#include <typeindex>
#include <utility>

#include "AQ_Database.hpp"
#include "AQ_Component.hpp"
namespace aquarius_engine {
	class AQ_GameObjectCtrl;
	class AQ_CompModel;

	class AQ_GameObject {
		friend class AQ_GameObjectCtrl;
	private:
		AQ_GameObjectCtrl* gameObjectCtrlPtr;
		std::string name;
		std::map<std::type_index, std::vector<std::pair<std::string, unsigned int>>> componentsKeys;
		AQ_Component** componentsCallbackPass;
		void** otherRefs;
		void (*startCallback)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis, 
			AQ_Component** components, void** otherRefs);
		void (*updateCallback)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis,
			AQ_Component** components, void** otherRefs);
	public:
		AQ_GameObject(AQ_GameObjectCtrl* gameObjectCtrl, std::string name);
		void setStartCallback(void (*startCallback)(AQ_GameObjectCtrl* gameObjectCtrl,
			AQ_GameObject* gameObjectThis, AQ_Component** components, void** otherRefs));
		void setUpdateCallback(void (*updateCallback)(AQ_GameObjectCtrl* gameObjectCtrl,
			AQ_GameObject* gameObjectThis, AQ_Component** components, void** otherRefs));
		~AQ_GameObject();
	};
}