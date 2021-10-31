#pragma once
#include <typeinfo>
#include <string>

namespace aquarius_engine {

	class AQ_GameObject;

	enum class AQ_EComponents {
		CAMERA, MODEL
	};

	class AQ_Component {
		friend class AQ_GameObject;
		friend class AQ_GameObjectCtrl;
	protected:
		AQ_GameObject* gameObjectThis;
		unsigned int databaseAccessKey;
		std::string name;
	public:
		AQ_GameObject* getGameObject();
		virtual ~AQ_Component() {}
	};
}