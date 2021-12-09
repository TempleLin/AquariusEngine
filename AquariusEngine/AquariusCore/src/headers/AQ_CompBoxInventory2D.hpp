#pragma once
#include "AQ_CompSimpleBox2D.hpp"
#include "AQ_CompBoxButton2D.hpp"
#include <glm/glm.hpp>
#include <vector>

namespace aquarius_engine {
	class AQ_CompBoxInventory2D : public AQ_CompSimpleBox2D, public AQ_IHoverClick {
	protected:
		unsigned int slotTexture;
		static unsigned int slotInstancingShaderID, slotInstancingUsageCount;
		static unsigned int* slotInstancingVertexBuffers; //0: vao, 1: vbo, 2:ebo, 3:instancing_vbo
		static int* slotShaderUniforms;
		bool rowMajor;
		float spacing;
		unsigned int slotCount;
		glm::vec2* translations;
		float slotSize;

		void checkCompileErrors(unsigned int shader, std::string type);
	public:
		AQ_CompBoxInventory2D(unsigned int shaderID, bool rowMajor, unsigned int slotCount, float slotSize);
		void setSlotTexture(std::string imageLocation, unsigned int wrap_s, unsigned int wrap_t,
			unsigned int min_filter, unsigned int mag_filter, bool hasAndUseAlpha);
		void setSlotsRange(glm::vec3 topLeftVertXYZ, glm::vec3 downRightVertXYZ);
		void setSpacing(float spacing);

		virtual bool hoverCheck(double cursorX, double cursorY, bool normalized);
		virtual bool clickCheck(double cursorX, double cursorY, bool normalized);
		virtual void draw();
		virtual void disable(bool disable);

		virtual void transformReset();
		virtual void transformRotate(glm::vec3 rotateVector, float angle);
		virtual void transformTranslate(glm::vec3 translateVector);
		virtual void transformScale(glm::vec3 scaleVector);
		virtual void setTransform(glm::mat4 transform);

		virtual ~AQ_CompBoxInventory2D();
	};
}