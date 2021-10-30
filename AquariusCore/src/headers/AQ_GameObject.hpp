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
		/*
		* @These references are useful when calling start and update methods.
		*/
		AQ_Component** componentsRefs;
		void** otherRefs;
		/*
		* @These get called from gameObjectCtrl for processing start and update of this gameObject.
		*/
		void (*startCallback)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis);
		void (*updateCallback)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis);
		void (*stopCallback)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis);
	public:
		AQ_GameObject(AQ_GameObjectCtrl* gameObjectCtrl, std::string name);

		void setComponentsRefs(AQ_Component** compsRefs);
		void setOtherRefs(void** otherRefs);
		AQ_Component** getComponentsRefs();
		void** getOtherRefs();

		void setCallbackFuncs(void (*start)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis),
			void (*update)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis),
			void (*stop)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis));
		~AQ_GameObject();
	};
}