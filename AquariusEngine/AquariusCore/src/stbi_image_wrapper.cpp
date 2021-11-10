#include "headers/stbi_image_wrapper.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace stbi_image_wrap {
	unsigned char* loadImage(std::string texturePath, int& width, int& height, int& nrChannels) {
		return stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	}
	void freeImage(unsigned char* data) {
		stbi_image_free(data);
	}
	void setFlipVerticallyOnLoad(bool trueOrFalse) {
		stbi_set_flip_vertically_on_load(trueOrFalse);
	}
}
