#pragma once
#include "AQ_CompSimpleBox2D.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace aquarius_engine {
	class AQ_GameObject;
	class AQ_GameObjectCtrl;

	class AQ_CompBoxButton2D : public AQ_CompSimpleBox2D {
	private:
		float fourVertsXYZ[12];
		void (*onHoverCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl);
		void (*onClickCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl);
		void normalizeCoordinate(double* cursorX, double* cursorY, int windowWidth, int windowHeight);
		void checkInButtonRange(double cursorX, double cursorY, bool normalized);
	public:
		AQ_CompBoxButton2D(unsigned int vao, unsigned int vbo, unsigned int ebo, int vertsCount);
		void setSensorRange(float topLeftVertXYZ[3], float topRightVertXYZ[3], float downRightVertXYZ[3], float downLeftVertXYZ[3]);
		void setListenHover(void (*onHoverCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl));
		void setListenClick(void (*onClickCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl));
		void hoverCheck(double cursorX, double cursorY, bool normalized);
		void clickCheck(double cursorX, double cursorY, bool normalized);
	};
}