#pragma once
#include <string>

namespace stbi_image_wrap {

	enum class ImageLoadingType {
		PNG, JPG
	};

	unsigned char* loadImage(std::string texturePath, int& width, int& height, int& nrChannels);
	void freeImage(unsigned char& data);
	void setFlipVerticallyOnLoad(bool trueOrFalse);
}
