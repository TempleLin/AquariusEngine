#include "headers/AQ_CompBoxInventory2D.hpp"

namespace aquarius_engine {
	AQ_CompBoxInvertory2D::AQ_CompBoxInvertory2D(unsigned int shaderID, bool rowMajor) : AQ_CompSimpleBox2D(shaderID), AQ_IHoverClick(), rowMajor(rowMajor) {

	}
	void AQ_CompBoxInvertory2D::setSlotTexture(std::string imageLocation, unsigned int wrap_s, unsigned int wrap_t, unsigned int min_filter, unsigned int mag_filter, bool hasAndUseAlpha)
	{
	}
	void AQ_CompBoxInvertory2D::setSlotsRange(glm::vec3 topLeftVertXYZ, glm::vec3 downRightVertXYZ)
	{
	}
	void AQ_CompBoxInvertory2D::setSpacing(float spacing)
	{
	}
	bool AQ_CompBoxInvertory2D::hoverCheck(double cursorX, double cursorY, bool normalized)
	{
		return false;
	}
	bool AQ_CompBoxInvertory2D::clickCheck(double cursorX, double cursorY, bool normalized)
	{
		return false;
	}
	void AQ_CompBoxInvertory2D::draw() {
		AQ_CompSimpleBox2D::draw();
	}
	void AQ_CompBoxInvertory2D::disable(bool disable) {
		AQ_IHoverClick::disable(disable);
	}
	void AQ_CompBoxInvertory2D::transformReset() {
		AQ_CompSimpleBox2D::transformReset();
	}
	void AQ_CompBoxInvertory2D::transformRotate(glm::vec3 rotateVector, float angle) {
		AQ_CompSimpleBox2D::transformRotate(rotateVector, angle);
	}
	void AQ_CompBoxInvertory2D::transformTranslate(glm::vec3 translateVector) {
		AQ_CompSimpleBox2D::transformTranslate(translateVector);
	}
	void AQ_CompBoxInvertory2D::transformScale(glm::vec3 scaleVector) {
		AQ_CompSimpleBox2D::transformScale(scaleVector);
	}
	void AQ_CompBoxInvertory2D::setTransform(glm::mat4 transform) {
		AQ_CompSimpleBox2D::setTransform(transform);
	}
}