#include "headers/AQ_CompBoxButton2D.hpp"
#include "headers/AQ_GameObjectCtrl.hpp"
#include "headers/AQ_GameObject.hpp"

namespace aquarius_engine {
	void AQ_CompBoxButton2D::normalizeCoordinate(double* cursorX, double* cursorY, int windowWidth, int windowHeight) {
		*cursorX = (*cursorX / windowWidth * 2) - 1;
		*cursorY = - ((*cursorY / windowHeight * 2) - 1);
	}

	void AQ_CompBoxButton2D::checkInButtonRange(double cursorX, double cursorY, bool normalized) {
		int windowWidth, windowHeight;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		std::cout << "cursorX: " << cursorX << "\n";
		std::cout << "cursorY: " << cursorY << "\n";
		std::cout << "windowWidth: " << windowWidth << "\n";
		std::cout << "windowHeight: " << windowHeight << "\n";
		if (_keepAspectRatio) {
			if (windowHeight > windowHeight) {
				windowHeight *= windowWidth / windowHeight;
			} else {
				windowWidth *= windowHeight / windowWidth;
			}
		}
		if (!normalized)
			normalizeCoordinate(&cursorX, &cursorY, windowWidth, windowHeight);
		std::cout << "cursorX after normalized: " << cursorX << "\n";
		std::cout << "cursorY after normalized: " << cursorY << "\n";
		std::cout << "fourVerts of button: " << "0: " << fourVertsXYZ[0] << ", 9: " << fourVertsXYZ[9]
			<< ", 3: " << fourVertsXYZ[3] << ", 6: " << fourVertsXYZ[6] << ", 1: " << fourVertsXYZ[1] << ", 4: "
			<< fourVertsXYZ[4] << ", 10: " << fourVertsXYZ[10] << ", 7: " << fourVertsXYZ[7] << "\n";
		if (cursorX >= fourVertsXYZ[0] && cursorX >= fourVertsXYZ[9] && cursorX <= fourVertsXYZ[3]
			&& cursorX <= fourVertsXYZ[6] && cursorY <= fourVertsXYZ[1] && cursorY <= fourVertsXYZ[4]
			&& cursorY >= fourVertsXYZ[10] && cursorY >= fourVertsXYZ[7]) {
			std::cout << "Cursor in button range\n";
		} else {
			std::cout << "Cursor not in button range\n";
		}
	}

	AQ_CompBoxButton2D::AQ_CompBoxButton2D(unsigned int vao, unsigned int vbo, unsigned int ebo, int vertsCount)
		: AQ_CompSimpleBox2D(vao, vbo, ebo, vertsCount), onHoverCallback(nullptr),
		onClickCallback(nullptr) {

	}

	void AQ_CompBoxButton2D::setSensorRange(float topLeftVertXYZ[3], float topRightVertXYZ[3], float downRightVertXYZ[3], float downLeftVertXYZ[3]) {
		if (!window) {
			window = getGameObject()->getGameObjectCtrl()->getSceneGameObjects()->getScene()->getCurrentWindow();
		}
		for (int i = 0; i < 3; i++) {
			fourVertsXYZ[i] = topLeftVertXYZ[i];
			fourVertsXYZ[3 + i] = topRightVertXYZ[i];
			fourVertsXYZ[6 + i] = downRightVertXYZ[i];
			fourVertsXYZ[9 + i] = downLeftVertXYZ[i];
		}
	}

	void AQ_CompBoxButton2D::setListenHover(void (*onHoverCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl)) {
		this->onHoverCallback = onHoverCallback;
	}

	void AQ_CompBoxButton2D::setListenClick(void (*onClickCallback)(AQ_GameObject* gameObjectThis, AQ_GameObjectCtrl* gameObjectCtrl)) {
		this->onClickCallback = onClickCallback;
	}

	void AQ_CompBoxButton2D::hoverCheck(double cursorX, double cursorY, bool normalized) {
		checkInButtonRange(cursorX, cursorY, normalized);
	}

	void AQ_CompBoxButton2D::clickCheck(double cursorX, double cursorY, bool normalized) {
		checkInButtonRange(cursorX, cursorY, normalized);
	}
}