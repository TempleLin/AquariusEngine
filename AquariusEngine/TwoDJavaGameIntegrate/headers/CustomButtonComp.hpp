#pragma once
#include <headers/AQ_CompBoxButton2D.hpp>

namespace aquarius_engine {
	class CustomButtonComp : public AQ_CompBoxButton2D {
	private:
		bool onHover;
	public:
		CustomButtonComp(unsigned int shaderID/*, unsigned int vao, unsigned int vbo, unsigned int ebo, int vertsCount*/);
		bool hoverCheck(double cursorX, double cursorY, bool normalized);
		bool clickCheck(double cursorX, double cursorY, bool normalized);
	};
}