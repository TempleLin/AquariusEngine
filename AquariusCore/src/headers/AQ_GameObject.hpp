#pragma once
#include <string>
#include <map>
#include <vector>
#include <glm/glm.hpp>
#include <type_traits>
#include <typeindex>
#include <utility>

#include "AQ_Database.hpp"
#include "AQ_Component.hpp"
#include "AQ_Transform.hpp"
namespace aquarius_engine {
	class AQ_GameObjectCtrl;
	class AQ_CompModel;

	class AQ_GameObject : public AQ_Transform{
		friend class AQ_GameObjectCtrl;
	private:
		AQ_GameObjectCtrl* gameObjectCtrlPtr;
		std::string name;
		glm::mat4 transform;
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

		AQ_GameObjectCtrl* getGameObjectCtrl();

		void setCallbackFuncs(void (*start)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis),
			void (*update)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis),
			void (*stop)(AQ_GameObjectCtrl* gameObjectCtrl, AQ_GameObject* gameObjectThis));

		virtual glm::mat4 getTransform();
		virtual void transformRotate(glm::vec3 rotateVector, float angle);
		virtual void transformTranslate(glm::vec3 translateVector);
		virtual void transformScale(glm::vec3 scaleVector);

		~AQ_GameObject();
	};
}