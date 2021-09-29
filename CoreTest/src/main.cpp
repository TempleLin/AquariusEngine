#include <iostream>

#include "headers/framebuffer_postprocess.h"
#include "headers/read_objmodel.h"

#include <headers/AQ_GlobalCtrl.h>

int main() {
	read_objmodel::callable_main();
	//framebuffer_postprocess::callable_main();
	//AQ_GlobalCtrl::LightsCtrl::addDirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(.5f, .5f, .5f), 1.f);
	std::cout << "Core Test End" << std::endl;
}