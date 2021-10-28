#pragma once
#include "AQ_Component.hpp"
#include "stbi_image_wrapper.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

namespace aquarius_engine {
	enum class _2DShapeType {
		CUBE
	};

	class AQ_Comp2DModel : public AQ_Component {
	private:
		struct ImageNamePair {
		public:
			std::string name;
			int width, height, nrChannels;
			unsigned int texture;
			ImageNamePair(std::string name, int width, int height, int nrChannels, unsigned int texture)
				: name(name), width(width), height(height), nrChannels(nrChannels), texture(texture) {
			}
			~ImageNamePair() {
			}
		};
		unsigned int vao, vbo;
		_2DShapeType shapeType;
		std::vector<ImageNamePair> images;
	public:

		AQ_Comp2DModel(unsigned int vao, unsigned int vbo, _2DShapeType shapeType) 
			: vao(vao), vbo(vbo), shapeType(shapeType) {
			
		}
		void addImage(std::string imageLocation, stbi_image_wrap::ImageLoadingType, std::string name) {
			int width, height, nrChannels;
			unsigned char* data = stbi_image_wrap::loadImage("imgs/container.jpg", width, height, nrChannels);
			if (data) {
				
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				//images.push_back(ImageNamePair(name, width, height, nrChannels, ));
			}
		}
		~AQ_Comp2DModel() {
		}
	};
}
