#include "headers/CustomButtonComp.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <headers/AQ_GameObjectCtrl.hpp>
#include <headers/AQ_GameObject.hpp>
#include <headers/AQ_GlobalCtrl.hpp>

namespace aquarius_engine {
	CustomButtonComp::CustomButtonComp(unsigned int shaderID/*, unsigned int vao, unsigned int vbo, unsigned int ebo, int vertsCount*/) : 
		AQ_CompBoxButton2D(shaderID/*, vao, vbo, ebo, vertsCount*/), onHover(false) {
	}

	// @Override
	bool CustomButtonComp::hoverCheck(double cursorX, double cursorY, bool normalized) {
		bool superCheck = AQ_CompBoxButton2D::hoverCheck(cursorX, cursorY, normalized);
		if (superCheck && !onHover) {
			onHover = true;
			std::cout << "On hover button\n";
			transformScale(glm::vec3(1.2f, 1.2f, 1.f));
			glUniformMatrix4fv(uniforms[3], 1, false, &(getTransform())[0][0]);
			return true;
		} else if (!superCheck && onHover){
			onHover = false;
			transformScale(glm::vec3(1.f / 1.2f, 1.f / 1.2f, 1.f));
			glUniformMatrix4fv(uniforms[3], 1, false, &(getTransform())[0][0]);
			return false;
		}
	}

	// @Override
	bool CustomButtonComp::clickCheck(double cursorX, double cursorY, bool normalized) {
		bool superCheck = AQ_CompBoxButton2D::clickCheck(cursorX, cursorY, normalized);
		if (superCheck) {
			std::cout << "On click button\n";
			static AQ_GlobalCtrl::AudioSystemCtrl* audioSystemCtrl = getGameObject()->getGameObjectCtrl()->getUniControls()->getGlobalCtrl()
				->getAudioSystemCtrl();
			audioSystemCtrl->play2D("assets/Sounds/SoundEffects/Testing/explosion.wav", false);
		}
		return superCheck;
	}
}
