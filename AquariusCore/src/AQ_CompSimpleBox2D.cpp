#include "headers/AQ_CompBoxButton2D.hpp"
#include "headers/AQ_GameObjectCtrl.hpp"
#include "headers/AQ_GameObject.hpp"
#include "headers/AQ_GlobalCtrl.hpp"

namespace aquarius_engine {
	AQ_CompSimpleBox2D::AQ_CompSimpleBox2D(unsigned int vao, unsigned int vbo, unsigned int ebo, int verticesCount)
		: vao(vao), vbo(vbo), ebo(ebo), verticesCount(verticesCount), shaderID(0), window(nullptr), _keepAspectRatio(false) {
	}

	void AQ_CompSimpleBox2D::setDiffuseTexture(std::string imageLocation, std::string name, unsigned int wrap_s, unsigned int wrap_t,
		unsigned int min_filter, unsigned int mag_filter, bool hasAndUseAlpha, int* returnTexIndex) {
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
		} else {
			throw std::string("ERROR: CANNOT LOAD IMAGE WITH GIVEN PATH--" + imageLocation);
		}
		setTexWrapFilter(wrap_s, wrap_t, min_filter, mag_filter);
	}

	void AQ_CompSimpleBox2D::setAnimSprites(std::vector<std::string> imagesLocations, unsigned int wrap_s, unsigned int wrap_t,
		unsigned int min_filter, unsigned int mag_filter, bool hasAndUseAlpha) {
		for (int i = 0; i < imagesLocations.size(); i++) {
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			int width, height, nrChannels;
			unsigned char* data = stbi_image_wrap::loadImage(imagesLocations.at(i), width, height, nrChannels);
			if (data) {
				if (!hasAndUseAlpha)
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				else
					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				animSprites.push_back(texture);
				stbi_image_wrap::freeImage(data);
			} else {
				throw std::string("ERROR: CANNOT LOAD IMAGE WITH GIVEN PATH--" + imagesLocations.at(i));
			}
			setTexWrapFilter(wrap_s, wrap_t, min_filter, mag_filter);
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
		uniforms = { glGetUniformLocation(shaderID, "windowWidth"), glGetUniformLocation(shaderID, "windowHeight"),
		glGetUniformLocation(shaderID, "keepAspectRatio"), glGetUniformLocation(shaderID, "offsetMat") };
	}

	void AQ_CompSimpleBox2D::useShader() {
		if (!shaderID)
			std::cout << "WARNING: SHADER CAN'T BE USED, SHADER NOT SET.\n";
		glUseProgram(shaderID);
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

	void AQ_CompSimpleBox2D::setPreDrawCallback(void(*callback)(unsigned int shaderID, AQ_CompSimpleBox2D* simpleBox2DThis)) {
		this->preDrawCallback = callback;
	}

	void AQ_CompSimpleBox2D::keepAspectRatio() {
		_keepAspectRatio = true;
	}

	void AQ_CompSimpleBox2D::draw() {
		preDrawCallback(shaderID, this);
		if (!window)
			window = getGameObject()->getGameObjectCtrl()->getSceneGameObjects()->getScene()->getCurrentWindow();

		glUseProgram(shaderID);
		glActiveTexture(GL_TEXTURE0);
		bindTexture(0);
		glBindVertexArray(vao);

		int windWidth, windHeight;
		glfwGetWindowSize(window, &windWidth, &windHeight);
		glUniform1f(uniforms[0], (float)windWidth);
		glUniform1f(uniforms[1], (float)windHeight);
		glUniform1i(uniforms[2], _keepAspectRatio? GLFW_TRUE : GLFW_FALSE);
		glUniformMatrix4fv(uniforms[3], 1, false, &(getTransform())[0][0]);

		glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void AQ_CompSimpleBox2D::drawSpriteAnim(float timePassedInGame) {
		/*preDrawCallback(shaderID, this);
		if (!window)
			window = getGameObject()->getGameObjectCtrl()->getSceneGameObjects()->getScene()->getCurrentWindow();

		glUseProgram(shaderID);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, animSprites.at(0));
		glBindVertexArray(vao);

		int windWidth, windHeight;
		glfwGetWindowSize(window, &windWidth, &windHeight);
		glUniform1f(uniforms[0], (float)windWidth);
		glUniform1f(uniforms[1], (float)windHeight);
		glUniform1i(uniforms[2], _keepAspectRatio ? GLFW_TRUE : GLFW_FALSE);
		glUniformMatrix4fv(uniforms[3], 1, false, &(getTransform())[0][0]);

		glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);*/

		preDrawCallback(shaderID, this);
		if (!window)
			window = getGameObject()->getGameObjectCtrl()->getSceneGameObjects()->getScene()->getCurrentWindow();
		glUseProgram(shaderID);
		/*std::cout << "0: " << (int)(timePassedInGame - (int)timePassedInGame) << "\n";
		std::cout << "1: " << (int)(timePassedInGame - (int)timePassedInGame) / .01f << "\n";
		std::cout << "2: " << (timePassedInGame - (int)timePassedInGame) << "\n";
		std::cout << "3: " << (int)((timePassedInGame - (int)timePassedInGame) / .01f / animSprites.size()) << "\n";
		std::cout << "4: " << animSprites.size() << "\n";*/
		//glBindTexture(GL_TEXTURE_2D, animSprites.at((int)((timePassedInGame - (int)timePassedInGame) / .01f / animSprites.size())));
		//std::cout << animSprites.at((int)((timePassedInGame - (int)timePassedInGame) / (1.f / (float)(animSprites.size())))) << "\n";
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, animSprites.at((int)((timePassedInGame - (int)timePassedInGame) / (1.f / (float)(animSprites.size())))));
		glBindVertexArray(vao);

		int windWidth, windHeight;
		glfwGetWindowSize(window, &windWidth, &windHeight);
		glUniform1f(uniforms[0], (float)windWidth);
		glUniform1f(uniforms[1], (float)windHeight);
		glUniform1i(uniforms[2], _keepAspectRatio ? GLFW_TRUE : GLFW_FALSE);
		glUniformMatrix4fv(uniforms[3], 1, false, &(getTransform())[0][0]);

		glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	AQ_CompSimpleBox2D::~AQ_CompSimpleBox2D() {
	}
}