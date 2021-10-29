#pragma once
#include "AQ_Component.hpp"
#include "stbi_image_wrapper.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

namespace aquarius_engine {
	class AQ_CompSimple2D : public AQ_Component {
	private:
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
		unsigned int* uniforms;
		char** uniformsNames;
		std::vector<TextureNamePair> textures;
		void(*preDrawCallback)(unsigned int, unsigned int*, const char**);
	public:

		AQ_CompSimple2D(unsigned int vao, unsigned int vbo, unsigned int ebo) : vao(vao), vbo(vbo), ebo(ebo) {
			
		}
		static void enableAlpha() {
			/*
			* @Note: These need to be set to have transparent background image.
			*/
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		}
		void addTexture(std::string imageLocation, stbi_image_wrap::ImageLoadingType, std::string name, 
			bool hasAndUseAlpha, bool bindTexture) {
			for (int i = 0; i < textures.size(); i++) {
				if (textures.at(i).name == name) {
					throw std::string("ERROR: IMAGE ADDED WAS SPECIFIED A NAME THAT ALREADY EXISTS");
				}
			}
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			int width, height, nrChannels;
			unsigned char* data = stbi_image_wrap::loadImage(imageLocation, width, height, nrChannels);
			if (data) {
				if (!hasAndUseAlpha)
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				else
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				textures.push_back(TextureNamePair(name, width, height, nrChannels, texture));
				stbi_image_wrap::freeImage(data);
				if (!bindTexture)
					glBindTexture(GL_TEXTURE_2D, 0);
			} else {
				throw std::string("ERROR: CANNOT LOAD IMAGE WITH GIVEN PATH--" + imageLocation);
			}
		}
		void setTexWrapFilter(unsigned int wrap_s, unsigned int wrap_t, unsigned int min_filter, unsigned int mag_filter) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		void setShaderID(unsigned int shaderID) {
			this->shaderID = shaderID;
		}
		void setUniforms(unsigned int* uniforms, char** uniformsNames) {
			this->uniforms = uniforms;
			this->uniformsNames = uniformsNames;
		}
		void bindTexture(std::string textureName) {
			for (int i = 0; i < textures.size(); i++) {
				if (textures.at(i).name == textureName) {
					glBindTexture(GL_TEXTURE_2D, textures.at(i).texture);
				}
			}
		}
		void setPreDrawCallback(void(*callback)(unsigned int shaderID, unsigned int* uniforms, const char** uniformsNames)) {
			this->preDrawCallback = callback;
		}
		void draw() {
			preDrawCallback(shaderID, uniforms, uniformsNames);
		}
		~AQ_CompSimple2D() {
			delete[] uniforms;
			delete[] uniformsNames;
		}
	};
}
