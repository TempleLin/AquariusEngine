#include "headers/AQ_Lights.h"

AQ_DirLight::AQ_DirLight(glm::vec3 _direction, glm::vec3 _color, float _intensity)
	: direction(_direction), color(_color), intensity(_intensity) {

}

AQ_PointLight::AQ_PointLight(glm::vec3 _position, float _radius, float _intensity)
	: position(_position), radius(_radius), intensity(_intensity) {
	constant = 1.f;
	// Setting radius less than 7 will have values as 7.
	if (_radius >= 0.f && _radius < 13.f) {
		linear = .7f;
		quadratic = 1.8f;
	} else if (_radius >= 13.f && _radius < 20.f) {
		linear = .35f;
		quadratic = .44f;
	} else if (_radius >= 20.f && _radius < 32.f) {
		linear = .22f;
		quadratic = .2f;
	} else if (_radius >= 32.f && _radius < 50.f) {
		linear = .14f;
		quadratic = .07f;
	} else if (_radius >= 50.f && _radius < 65.f) {
		linear = .09f;
		quadratic = .032f;
	} else if (_radius >= 65.f && _radius < 100.f) {
		linear = .07f;
		quadratic = .017f;
	} else if (_radius >= 100.f && _radius < 160.f) {
		linear = .045f;
		quadratic = .0075f;
	} else if (_radius >= 160.f && _radius < 200.f) {
		linear = .027f;
		quadratic = .0028f;
	} else if (_radius >= 200.f && _radius < 325.f) {
		linear = .022f;
		quadratic = .0019f;
	} else if (_radius >= 325.f && _radius < 600.f) {
		linear = .014f;
		quadratic = .0007f;
	} else if (_radius >= 600.f && _radius < 3250.f) {
		linear = .007f;
		quadratic = .0002f;
	} else if (_radius >= 3250.f) {
		linear = .0014f;
		quadratic - .000007f;
	} else {
		linear = 0.f;
		quadratic = 0.f;
	}
}

AQ_SpotLight::AQ_SpotLight(glm::vec3 _position, glm::vec3 _direction, float _cutoffAngle, float _intensity)
	: position(_position), direction(_direction), cuttoffAngle(_cutoffAngle), intensity(_intensity) {

}