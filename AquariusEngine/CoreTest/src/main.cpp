#include <iostream>


#include "headers/framebuffer_postprocess.h"
#include "headers/read_objmodel.h"
#include "headers/gamma_correction.h"
#include "headers/shadow_mapping.h"

#include <headers/AQ_GlobalCtrl.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
	read_objmodel::callable_main();
	//framebuffer_postprocess::callable_main();
	//AQ_GlobalCtrl::LightsCtrl::addDirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(.5f, .5f, .5f), 1.f);
	//gamma_correction::callable_main();
	//shadow_mapping::main();
	std::cout << "Core Test End" << std::endl;
}