#pragma once
#include "AQ_CompSimpleBox2D.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

namespace aquarius_engine {
	class AQ_GameObject;
	class AQ_GameObjectCtrl;

	class AQ_CompBoxButton2D : public AQ_CompSimpleBox2D {
	private:
		glm::vec3 fourVertsXYZ[4];
		glm::vec3 fourVertsRatioChanged[4];
		bool _disableButton;
		void (*onHoverCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl);
		void (*onClickCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl);
		void ratioChangeVerts(double* cursorX, double* cursorY, int windowWidth, int windowHeight);
		bool checkInButtonRange(double cursorX, double cursorY, bool normalized);
	public:
		AQ_CompBoxButton2D(unsigned int vao, unsigned int vbo, unsigned int ebo, int vertsCount);
		void setSensorRange(glm::vec3 topLeftVertXYZ, glm::vec3 topRightVertXYZ, glm::vec3 downRightVertXYZ, glm::vec3 downLeftVertXYZ);
		void translateSensorRange(glm::vec3 translateVector);
		void scaleSensorRange(glm::vec3 scaleVector);
		void setListenHover(void (*onHoverCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl));
		void setListenClick(void (*onClickCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl));
		virtual bool hoverCheck(double cursorX, double cursorY, bool normalized);
		virtual bool clickCheck(double cursorX, double cursorY, bool normalized);
		virtual void draw();
		void disableButton(bool disable);
	};
}