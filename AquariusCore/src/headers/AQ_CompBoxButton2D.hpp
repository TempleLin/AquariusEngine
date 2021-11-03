#pragma once
#include "AQ_CompSimple2D.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace aquarius_engine {
	class AQ_GameObject;
	class AQ_GameObjectCtrl;

	class AQ_CompBoxButton2D : public AQ_CompSimple2D {
	private:
		void (*onHoverCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl);
		void (*onClickCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl);
		double* cursorXRef;
		double* cursorYRef;
	public:
		AQ_CompBoxButton2D(double* cursorXRef, double* cursorYRef, unsigned int vao, unsigned int vbo, unsigned int ebo, int vertsCount) 
			: AQ_CompSimple2D(vao, vbo, ebo, vertsCount), cursorXRef(cursorXRef), cursorYRef(cursorYRef), onHoverCallback(nullptr),
			onClickCallback(nullptr) {

		}
		void setListenHover(void (*onHoverCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl)) {
			this->onHoverCallback = onHoverCallback;
		}
		void setListenClick(void (*onClickCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl)) {
			this->onClickCallback = onClickCallback;
		}
		void hoverListen() {

		}
		void clickListen() {

		}
	};
}