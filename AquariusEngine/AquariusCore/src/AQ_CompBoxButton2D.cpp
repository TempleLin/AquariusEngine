#include "headers/AQ_CompBoxButton2D.hpp"
#include "headers/AQ_GameObjectCtrl.hpp"
#include "headers/AQ_GameObject.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace aquarius_engine {
	void AQ_CompBoxButton2D::ratioChangeVerts(double* cursorX, double* cursorY, int windowWidth, int windowHeight) {
		*cursorX = (*cursorX / windowWidth * 2) - 1;
		*cursorY = - ((*cursorY / windowHeight * 2) - 1);
		for (int i = 0; i < 4; i++) {
			fourVertsRatioChanged[i].x = fourVertsXYZ[i].x;
			fourVertsRatioChanged[i].y = fourVertsXYZ[i].y;
		}
		if (_keepAspectRatio) {
			if (windowHeight > windowWidth) {
				float yRange = fourVertsXYZ[0].y - fourVertsXYZ[3].y;
				float offsetRange = (yRange - (yRange * ((float)windowWidth / (float)windowHeight))) / 2.f;
				fourVertsRatioChanged[0].y -= offsetRange;
				fourVertsRatioChanged[1].y -= offsetRange;
				fourVertsRatioChanged[2].y += offsetRange;
				fourVertsRatioChanged[3].y += offsetRange;
				for (int i = 0; i < 4; i++) {
					fourVertsRatioChanged[i].x = fourVertsXYZ[i].x;
				}
			} else {
				float xRange = fourVertsXYZ[1].x - fourVertsXYZ[0].x;
				float offsetRange = (xRange - (xRange * ((float)windowHeight / (float)windowWidth))) / 2.f;
				fourVertsRatioChanged[0].x += offsetRange;
				fourVertsRatioChanged[1].x -= offsetRange;
				fourVertsRatioChanged[2].x -= offsetRange;
				fourVertsRatioChanged[3].x += offsetRange;
				for (int i = 0; i < 4; i++) {
					fourVertsRatioChanged[i].y = fourVertsXYZ[i].y;
				}
			}
		}
	}

	bool AQ_CompBoxButton2D::checkInButtonRange(double cursorX, double cursorY, bool normalized) {
		if (_disableButton) return false;

		double windowWidth{}, windowHeight{};
		int tempWindWidth{ (int)windowWidth }, tempWindHeight{ (int)windowHeight };
		glfwGetWindowSize(window, &tempWindWidth, &tempWindHeight);
		windowWidth = tempWindWidth;
		windowHeight = tempWindHeight;

		if (!normalized)
			ratioChangeVerts(&cursorX, &cursorY, windowWidth, windowHeight);


		if (cursorX >= fourVertsRatioChanged[0].x && cursorX >= fourVertsRatioChanged[3].x && cursorX <= fourVertsRatioChanged[1].x && cursorX <= fourVertsRatioChanged[2].x
			&& cursorY <= fourVertsRatioChanged[0].y && cursorY <= fourVertsRatioChanged[1].y && cursorY >= fourVertsRatioChanged[2].y && cursorY >= fourVertsRatioChanged[3].y) {
			return true;
		} else {
			return false;
		}
		
	}

	AQ_CompBoxButton2D::AQ_CompBoxButton2D(unsigned int vao, unsigned int vbo, unsigned int ebo, int vertsCount)
		: AQ_CompSimpleBox2D(vao, vbo, ebo, vertsCount), AQ_IHoverClick(), _disableButton(false) {

	}

	void AQ_CompBoxButton2D::setSensorRange(glm::vec3 topLeftVertXYZ, glm::vec3 topRightVertXYZ, glm::vec3 downRightVertXYZ, glm::vec3 downLeftVertXYZ) {
		if (!window) {
			window = getGameObject()->getGameObjectCtrl()->getSceneGameObjects()->getScene()->getCurrentWindow();
		}
		fourVertsXYZ[0] = topLeftVertXYZ;
		fourVertsXYZ[1] = topRightVertXYZ;
		fourVertsXYZ[2] = downRightVertXYZ;
		fourVertsXYZ[3] = downLeftVertXYZ;
	}

	void AQ_CompBoxButton2D::translateSensorRange(glm::vec3 translateVector) {
		for (int i = 0; i < 4; i++) {
			fourVertsXYZ[i].x += translateVector.x;
			fourVertsXYZ[i].y += translateVector.y;
			fourVertsXYZ[i].z += translateVector.z;
		}
	}

	void AQ_CompBoxButton2D::scaleSensorRange(glm::vec3 scaleVector) {
		float xRange = fourVertsXYZ[1].x - fourVertsXYZ[0].x;
		float yRange = fourVertsXYZ[0].y - fourVertsXYZ[3].y;
		float xTransform = xRange - (xRange * scaleVector.x);
		float yTransform = yRange - (yRange * scaleVector.y);

		fourVertsXYZ[0].x += (xTransform / 2);
		fourVertsXYZ[1].x -= (xTransform / 2);
		fourVertsXYZ[2].x -= (xTransform / 2);
		fourVertsXYZ[3].x += (xTransform / 2);

		fourVertsXYZ[0].y -= (yTransform / 2);
		fourVertsXYZ[1].y -= (yTransform / 2);
		fourVertsXYZ[2].y += (yTransform / 2);
		fourVertsXYZ[3].y += (yTransform / 2);
	}

	bool AQ_CompBoxButton2D::hoverCheck(double cursorX, double cursorY, bool normalized) {
		return checkInButtonRange(cursorX, cursorY, normalized);
	}

	bool AQ_CompBoxButton2D::clickCheck(double cursorX, double cursorY, bool normalized) {
		return checkInButtonRange(cursorX, cursorY, normalized);
	}

	void AQ_CompBoxButton2D::draw() {
		if (_disableButton) return;
		AQ_CompSimpleBox2D::draw();
	}

	void AQ_CompBoxButton2D::disable(bool disable) {
		_disableButton = disable;
	}
}