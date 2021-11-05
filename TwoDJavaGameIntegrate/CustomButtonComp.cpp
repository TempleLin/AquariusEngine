#include "headers/CustomButtonComp.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <headers/AQ_GameObjectCtrl.hpp>
#include <headers/AQ_GameObject.hpp>

namespace aquarius_engine {
	CustomButtonComp::CustomButtonComp(unsigned int vao, unsigned int vbo, unsigned int ebo, int vertsCount) : 
		AQ_CompBoxButton2D(vao, vbo, ebo, vertsCount), onHover(false) {
		offsetMatrix = glm::translate(offsetMatrix, glm::vec3(.5f, 0.f, 0.f));
		offsetMatrix = glm::scale(offsetMatrix, glm::vec3(1.f, .4f, 1.f));
	}

	// @Override
	bool CustomButtonComp::hoverCheck(double cursorX, double cursorY, bool normalized) {
		bool superCheck = AQ_CompBoxButton2D::hoverCheck(cursorX, cursorY, normalized);
		if (superCheck && !onHover) {
			onHover = true;
			offsetMatrix = glm::scale(offsetMatrix, glm::vec3(1.2f, 1.2f, 1.f));
			glUniformMatrix4fv(uniforms[3], 1, false, &offsetMatrix[0][0]);
			return true;
		} else if (!superCheck && onHover){
			onHover = false;
			offsetMatrix = glm::scale(offsetMatrix, glm::vec3(1.f / 1.2f, 1.f / 1.2f, 1.f));
			glUniformMatrix4fv(uniforms[3], 1, false, &offsetMatrix[0][0]);
			return false;
		}
	}

	// @Override
	bool CustomButtonComp::clickCheck(double cursorX, double cursorY, bool normalized) {
		return AQ_CompBoxButton2D::clickCheck(cursorX, cursorY, normalized);
	}
}
