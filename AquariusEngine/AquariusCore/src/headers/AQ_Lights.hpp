#pragma once
#include <glm/glm.hpp>

namespace aquarius_engine {
	///*
	//* @Directional light doesn't need position (Like a sun in Blender which has (fake) inifinite distance).
	//*/
	//struct AQ_DirLight {
	//	friend class AQ_Database;
	//	friend class AQ_GlobalCtrl;
	//private:
	//	glm::vec3 direction;
	//	glm::vec3 color;
	//	float intensity;
	//	AQ_DirLight(glm::vec3 _direction, glm::vec3 _color, float _intensity);
	//};

	///*
	//* @Point light falloffs more as distance grows. Term is "Attenuation".
	//*  If range between light and object > distance, the light will have no effect.
	//*  Three factors below are used for its calc:
	//*
	//* Distance	Constant	Linear	Quadratic
	//*	7		1.0			0.7		1.8
	//*	13		1.0			0.35	0.44
	//*	20		1.0			0.22	0.20
	//*	32		1.0			0.14	0.07
	//*	50		1.0			0.09	0.032
	//*	65		1.0			0.07	0.017
	//*	100		1.0			0.045	0.0075
	//*	160		1.0			0.027	0.0028
	//*	200		1.0			0.022	0.0019
	//*	325		1.0			0.014	0.0007
	//*	600		1.0			0.007	0.0002
	//*	3250	1.0			0.0014	0.000007
	//*
	//*
	//* @Brightness =
	//*	LightIntensity / (Constant + Linear * Distance + Quadratic * Distance^2)
	//*/

	//struct AQ_PointLight {
	//	friend class AQ_Database;
	//	friend class AQ_GlobalCtrl;
	//private:
	//	glm::vec3 position;
	//	float radius;
	//	float constant, linear, quadratic;
	//	float intensity;
	//	AQ_PointLight(glm::vec3 _position, float _radius, float _intensity);
	//};

	///*
	//* @Cutoff angle specifies the spotlight's radius. Everything outside this angle is not lit by the spotlight.
	//*/
	//struct AQ_SpotLight {
	//	friend class AQ_Database;
	//	friend class AQ_GlobalCtrl;
	//private:
	//	glm::vec3 position;
	//	glm::vec3 direction;
	//	float cuttoffAngle;
	//	float intensity;
	//	AQ_SpotLight(glm::vec3 _position, glm::vec3 _direction, float _cutoffAngle, float _intensity);
	//};
}