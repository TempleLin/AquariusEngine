#include "headers/AQ_CompBoxButton2D.hpp"
#include "headers/AQ_GameObjectCtrl.hpp"
#include "headers/AQ_GameObject.hpp"

namespace aquarius_engine {
	AQ_CompSimpleBox2D::AQ_CompSimpleBox2D(unsigned int vao, unsigned int vbo, unsigned int ebo, int verticesCount)
		: vao(vao), vbo(vbo), ebo(ebo), verticesCount(verticesCount), shaderID(0), window(nullptr), _keepAspectRatio(false),
		offsetMatrix(glm::mat4(1.f)) {

	}

	void AQ_CompSimpleBox2D::addTexture(std::string imageLocation, std::string name,
		bool hasAndUseAlpha, bool bindTexture, int* returnTexIndex) {
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
			*returnTexIndex = textures.size() - 1;
			stbi_image_wrap::freeImage(data);
			if (!bindTexture)
				glBindTexture(GL_TEXTURE_2D, 0);
		} else {
			throw std::string("ERROR: CANNOT LOAD IMAGE WITH GIVEN PATH--" + imageLocation);
		}
	}

	void AQ_CompSimpleBox2D::setTexWrapFilter(unsigned int wrap_s, unsigned int wrap_t, unsigned int min_filter, unsigned int mag_filter) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
	}

	void AQ_CompSimpleBox2D::setShaderID(unsigned int shaderID) {
		this->shaderID = shaderID;
	}

	void AQ_CompSimpleBox2D::useShader() {
		if (!shaderID)
			std::cout << "WARNING: SHADER CAN'T BE USED, SHADER NOT SET.\n";
		glUseProgram(shaderID);
	}

	void AQ_CompSimpleBox2D::setUniforms(const char** uniformsNames, int uniformsCount) {
		if (!shaderID) {
			std::cout << "WARNING: UNIFORMs CAN'T BE SET, SHADER NOT SET.\n";
		}
		this->uniformsNames = uniformsNames;
		this->uniformsCount = uniformsCount;
		uniforms = new unsigned int[uniformsCount];
		for (int i = 0; i < uniformsCount; i++) {
			uniforms[i] = glGetUniformLocation(shaderID, uniformsNames[i]);
		}
	}

	void AQ_CompSimpleBox2D::activateTexture(unsigned int index) {
		glActiveTexture(index);
	}

	void AQ_CompSimpleBox2D::bindTexture(std::string textureName) {
		for (int i = 0; i < textures.size(); i++) {
			if (textures.at(i).name == textureName) {
				glBindTexture(GL_TEXTURE_2D, textures.at(i).texture);
			}
		}
	}

	void AQ_CompSimpleBox2D::bindTexture(int index) {
		glBindTexture(GL_TEXTURE_2D, textures.at(index).texture);
	}

	void AQ_CompSimpleBox2D::setPreDrawCallback(void(*callback)(unsigned int shaderID, unsigned int* uniforms, AQ_CompSimpleBox2D* simpleBox2DThis)) {
		this->preDrawCallback = callback;
	}

	void AQ_CompSimpleBox2D::keepAspectRatio() {
		_keepAspectRatio = true;
	}

	glm::mat4 AQ_CompSimpleBox2D::getOffsetMatrix() {
		return offsetMatrix;
	}

	void AQ_CompSimpleBox2D::draw() {
		preDrawCallback(shaderID, uniforms, this);
		if (!window)
			window = getGameObject()->getGameObjectCtrl()->getSceneGameObjects()->getScene()->getCurrentWindow();

		int windWidth, windHeight;
		glfwGetWindowSize(window, &windWidth, &windHeight);
		glUniform1i(uniforms[2], _keepAspectRatio? GLFW_TRUE : GLFW_FALSE);
		glUniform1i(uniforms[0], windWidth);
		glUniform1i(uniforms[1], windHeight);
		bindTexture(0);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	AQ_CompSimpleBox2D::~AQ_CompSimpleBox2D() {
		delete[] uniforms;
		delete[] uniformsNames;
	}
}