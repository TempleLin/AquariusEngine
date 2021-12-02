#include "headers/AQ_CompBoxButton2D.hpp"
#include "headers/AQ_GameObjectCtrl.hpp"
#include "headers/AQ_GameObject.hpp"
#include "headers/AQ_GlobalCtrl.hpp"

namespace aquarius_engine {
	//0: vao, 1: vbo, 2: ebo
	unsigned int* AQ_CompSimpleBox2D::vertexBuffers{ nullptr };
	//Count of AQ_CompSimpleBox2D class objects or its derived objects. when turns 0, the vertexBuffers gets deleted.
	int AQ_CompSimpleBox2D::usageCount{ 0 };

	AQ_CompSimpleBox2D::AQ_CompSimpleBox2D(unsigned int shaderID/*, unsigned int vao, unsigned int vbo, unsigned int ebo, int verticesCount*/)
		: /*vao(vao), vbo(vbo), ebo(ebo), */color(new float[]{1.f, 1.f, 1.f}), window(nullptr), _keepAspectRatio(false) {
		setShaderID(shaderID);
		usageCount++;
		if (!vertexBuffers) {
			vertexBuffers = new unsigned int[3];
			float vertices[] = {
				// positions          // colors           // texture coords
				 0.5f,  0.5f, 0.f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
				 0.5f, -0.5f, 0.f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
				-0.5f, -0.5f, 0.f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
				-0.5f,  0.5f, 0.f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left 
			};
			unsigned int indices[] = {  // note that we start from 0!
				0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
			};
			glGenVertexArrays(1, &vertexBuffers[0]);
			glBindVertexArray(vertexBuffers[0]);

			glGenBuffers(1, &vertexBuffers[1]);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffers[1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glGenBuffers(1, &vertexBuffers[2]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBuffers[2]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// color attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			// texture coord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);
		}
	}

	void AQ_CompSimpleBox2D::addDiffuseTexture(std::string imageLocation, std::string name, unsigned int wrap_s, unsigned int wrap_t,
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

	void AQ_CompSimpleBox2D::switchDiffuseTexture(std::string name) {
		for (int i = 0; i < textures.size(); i++) {
			if (textures.at(i).name == name) {
				auto temp = textures.at(0);
				textures.at(0) = textures.at(i);
				textures.at(i) = temp;
				break;
			}
		}
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
		glGetUniformLocation(shaderID, "keepAspectRatio"), glGetUniformLocation(shaderID, "offsetMat"), glGetUniformLocation(shaderID, "color"), 
		glGetUniformLocation(shaderID, "useTexture") };
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

	void AQ_CompSimpleBox2D::keepAspectRatio() {
		_keepAspectRatio = true;
	}

	void AQ_CompSimpleBox2D::setColor(float r, float g, float b) {
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}
	float* AQ_CompSimpleBox2D::getColor() {
		return color;
	}

	void AQ_CompSimpleBox2D::draw() {
		if (!window)
			window = getGameObject()->getGameObjectCtrl()->getSceneGameObjects()->getScene()->getCurrentWindow();

		glUseProgram(shaderID);
		glActiveTexture(GL_TEXTURE0);

		if (textures.size()) {
			bindTexture(0);
		} else {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glBindVertexArray(vertexBuffers[0]);

		int windWidth, windHeight;
		glfwGetWindowSize(window, &windWidth, &windHeight);
		glUniform1f(uniforms[0], (float)windWidth);
		glUniform1f(uniforms[1], (float)windHeight);
		glUniform1i(uniforms[2], _keepAspectRatio? GLFW_TRUE : GLFW_FALSE);
		glUniformMatrix4fv(uniforms[3], 1, false, &(getTransform())[0][0]);
		glUniform3fv(uniforms[4], 1, this->color);
		glUniform1i(uniforms[5], textures.size() ? true : false);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void AQ_CompSimpleBox2D::drawSpriteAnim(float timePassedInGame) {
		if (!window)
			window = getGameObject()->getGameObjectCtrl()->getSceneGameObjects()->getScene()->getCurrentWindow();
		glUseProgram(shaderID);
		if (animSprites.size()) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, animSprites.at((int)((timePassedInGame - (int)timePassedInGame) / (1.f / (float)(animSprites.size())))));
		} else {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		glBindVertexArray(vertexBuffers[0]);

		int windWidth, windHeight;
		glfwGetWindowSize(window, &windWidth, &windHeight);
		glUniform1f(uniforms[0], (float)windWidth);
		glUniform1f(uniforms[1], (float)windHeight);
		glUniform1i(uniforms[2], _keepAspectRatio ? GLFW_TRUE : GLFW_FALSE);
		glUniformMatrix4fv(uniforms[3], 1, false, &(getTransform())[0][0]);
		glUniform3fv(uniforms[4], 1, this->color);
		glUniform1i(uniforms[5], animSprites.size() ? true : false);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	AQ_CompSimpleBox2D::~AQ_CompSimpleBox2D() {
		delete[] color;
		if (!usageCount && vertexBuffers) {
			glDeleteBuffers(2, &vertexBuffers[1]);
			glDeleteVertexArrays(1, vertexBuffers);
			delete[] vertexBuffers;
		}
		for (int i = 0; i < textures.size(); i++) {
			glDeleteTextures(1, &(textures.at(i).texture));
		}
	}
}