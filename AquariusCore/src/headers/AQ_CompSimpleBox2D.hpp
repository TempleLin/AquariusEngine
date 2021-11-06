#pragma once
#include "AQ_Component.hpp"
#include "stbi_image_wrapper.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>

namespace aquarius_engine {
	class AQ_CompSimpleBox2D : public AQ_Component {
	protected:
		struct TextureNamePair {
		public:
			std::string name;
			int width, height, nrChannels;
			unsigned int texture;
			TextureNamePair(std::string name, int width, int height, int nrChannels, unsigned int texture)
				: name(name), width(width), height(height), nrChannels(nrChannels), texture(texture) {
			}
		};
		unsigned int vao, vbo, ebo, shaderID;
		std::vector<int> uniforms;
		int uniformsCount, verticesCount;
		const char** uniformsNames;
		std::vector<TextureNamePair> textures;
		void(*preDrawCallback)(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis);
		bool _keepAspectRatio;
		glm::mat4 offsetMatrix;
		GLFWwindow* window;
	public:

		AQ_CompSimpleBox2D(unsigned int vao, unsigned int vbo, unsigned int ebo, int verticesCount);
		void addDiffuseTexture(std::string imageLocation, std::string name,
			bool hasAndUseAlpha, int* returnTexIndex);
		void setTexWrapFilter(unsigned int wrap_s, unsigned int wrap_t, unsigned int min_filter, unsigned int mag_filter);
		void setShaderID(unsigned int shaderID);
		void useShader();
		void activateTexture(unsigned int index);
		void bindTexture(std::string textureName);
		void bindTexture(int index);
		void setPreDrawCallback(void(*callback)(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis));
		void keepAspectRatio();
		std::vector<int>& getUniforms();
		glm::mat4 getOffsetMatrix();
		void draw();
		~AQ_CompSimpleBox2D();
	};
}
