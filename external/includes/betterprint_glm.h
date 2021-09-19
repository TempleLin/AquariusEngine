#pragma once
#include <glm/glm.hpp>

//Needs to be removed when finished design.
#define GLMSIMPLE_TO_STRING_C

#if defined(GLMSIMPLE_TO_STRING_CPP)
#include <string>

template <typename T>
inline std::string glm_simpleto_string(T glm_object) {
	if (typeid(glm_object) == typeid(glm::vec1)) {
		return "(" + std::to_string(glm_object[0]) + ")";
	} else if (typeid(glm_object) == typeid(glm::vec2)) {
		return "(" + std::to_string(glm_object[0]) + "," + std::to_string(glm_object[1]) + ")";
	} else if (typeid(glm_object) == typeid(glm::vec3)) {
		return "(" + std::to_string(glm_object[0]) + "," + std::to_string(glm_object[1]) + "," 
			+ std::to_string(glm_object[2]) + ")";
	} else if (typeid(glm_object) == typeid(glm::vec4)) {
		return "(" + std::to_string(glm_object[0]) + "," + std::to_string(glm_object[1]) + "," 
			+ std::to_string(glm_object[2]) + "," + std::to_string(glm_object[3]) + ")";
	} else if (typeif(glm_object) == typeid(glm::mat2)) {
		//return 
	}
}
#elif defined(GLMSIMPLE_TO_STRING_C)
#include <string.h>
#define PRIVATEFUNCTION
#ifdef PRIVATEFUNCTION
char* simple_to_string_vec1(glm::vec1 vec) {
	
}
char* simple_to_string_vec2(glm::vec2 vec) {

}
char* simple_to_string_vec3(glm::vec3 vec) {

}
#endif // PRIVATEFUNCTION

#define glm_simpleto_string(X) _Generic((X), \
              glm::vec1: simple_to_string_vec1, \
                  glm::vec2: simple_to_string_vec2,  \
                    glm::vec3: simple_to_string_vec3  \
)(X)

#undef PRIVATEFUNCTION
#endif // BETTERPRINT_CPP

