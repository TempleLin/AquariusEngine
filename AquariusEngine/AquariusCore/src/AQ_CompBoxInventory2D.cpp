#include "headers/AQ_CompBoxInventory2D.hpp"
#include "headers/stbi_image_wrapper.hpp"
#include "headers/AQ_Shader.hpp"

namespace aquarius_engine {
	unsigned int AQ_CompBoxInventory2D::slotInstancingShaderID{ 0 };
	unsigned int* AQ_CompBoxInventory2D::slotInstancingVertexBuffers{ nullptr };
	unsigned int AQ_CompBoxInventory2D::slotInstancingUsageCount{ 0 };
	int* AQ_CompBoxInventory2D::slotShaderUniforms{ nullptr };

	AQ_CompBoxInventory2D::AQ_CompBoxInventory2D(unsigned int shaderID, bool rowMajor, unsigned int slotCount) 
		: AQ_CompSimpleBox2D(shaderID), AQ_IHoverClick(), rowMajor(rowMajor), slotTexture(0), slotCount(slotCount) {
		if (!slotInstancingShaderID) {
			AQ_Shader slotInstancingShader("../AquariusCore/shaders/two_d_slot_tex_vs.glsl", "../AquariusCore/shaders/two_d_slot_tex_fs.glsl");
			slotInstancingShader.use();
			slotInstancingShaderID = slotInstancingShader.ID;
		}
		if (!slotShaderUniforms) {
			slotShaderUniforms = new int[] {
				glGetUniformLocation(shaderID, "windowWidth"), glGetUniformLocation(shaderID, "windowHeight"),
					glGetUniformLocation(shaderID, "keepAspectRatio"), glGetUniformLocation(shaderID, "offsetMat"), glGetUniformLocation(shaderID, "color"),
					glGetUniformLocation(shaderID, "useTexture")
			};
		}
		if (!slotInstancingVertexBuffers) {
			slotInstancingVertexBuffers = new unsigned int[4]{ 0,0,0,0 };
			float vertices[] = {
				-0.05f,  0.05f, -.001f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
				 0.05f, -0.05f, -.001f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
				-0.05f, -0.05f, -.001f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
				-0.05f,  0.05f, -.001f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
				 0.05f, -0.05f, -.001f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
				 0.05f,  0.05f, -.001f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f
			};
			glGenVertexArrays(1, &slotInstancingVertexBuffers[0]);
			glBindVertexArray(slotInstancingVertexBuffers[0]);

			glGenBuffers(1, &slotInstancingVertexBuffers[1]);
			glBindBuffer(GL_ARRAY_BUFFER, slotInstancingVertexBuffers[1]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			// position attribute
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			// color attribute
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
			// texture coord attribute
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);

			glm::vec2 translations[100];
			int index = 0;
			float offset = 0.1f;
			for (int y = -10; y < 10; y += 2)
			{
				for (int x = -10; x < 10; x += 2)
				{
					glm::vec2 translation;
					translation.x = (float)x / 10.0f + offset;
					translation.y = (float)y / 10.0f + offset;
					translations[index++] = translation;
				}
			}

			glGenBuffers(1, &slotInstancingVertexBuffers[3]);
			glBindBuffer(GL_ARRAY_BUFFER, slotInstancingVertexBuffers[3]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
			// also set instance data
			glEnableVertexAttribArray(3);
			//glBindBuffer(GL_ARRAY_BUFFER, slotInstancingVertexBuffers[3]); // this attribute comes from a different vertex buffer
			glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glVertexAttribDivisor(3, 1); // tell OpenGL this is an instanced vertex attribute. (Here the translations values are vec2, so needs to pass two values per index, giving two values per instance.)
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		slotInstancingUsageCount++;
	}
	void AQ_CompBoxInventory2D::setSlotTexture(std::string imageLocation, unsigned int wrap_s, unsigned int wrap_t, unsigned int min_filter, unsigned int mag_filter, bool hasAndUseAlpha) {
		if (slotTexture) {
			glDeleteTextures(1, &slotTexture);
		}
		glGenTextures(1, &slotTexture);
		glBindTexture(GL_TEXTURE_2D, slotTexture);
		int width, height, nrChannels;
		unsigned char* data = stbi_image_wrap::loadImage(imageLocation, width, height, nrChannels);
		if (data) {
			if (!hasAndUseAlpha)
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			else
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_wrap::freeImage(data);
		} else {
			throw std::string("ERROR: CANNOT LOAD IMAGE WITH GIVEN PATH--" + imageLocation);
		}
		setTexWrapFilter(wrap_s, wrap_t, min_filter, mag_filter);
		glUseProgram(slotInstancingShaderID);
		//glUniform1i()
	}
	void AQ_CompBoxInventory2D::setSlotsRange(glm::vec3 topLeftVertXYZ, glm::vec3 downRightVertXYZ)
	{
	}
	void AQ_CompBoxInventory2D::setSpacing(float spacing)
	{
	}
	bool AQ_CompBoxInventory2D::hoverCheck(double cursorX, double cursorY, bool normalized)
	{
		return false;
	}
	bool AQ_CompBoxInventory2D::clickCheck(double cursorX, double cursorY, bool normalized)
	{
		return false;
	}
	void AQ_CompBoxInventory2D::draw() {
		AQ_CompSimpleBox2D::draw();
		glUseProgram(slotInstancingShaderID);
		glBindVertexArray(slotInstancingVertexBuffers[0]);

		int windWidth, windHeight;
		glfwGetWindowSize(window, &windWidth, &windHeight);
		glUniform1f(slotShaderUniforms[0], (float)windWidth);
		glUniform1f(slotShaderUniforms[1], (float)windHeight);
		glUniform1i(slotShaderUniforms[2], _keepAspectRatio ? GLFW_TRUE : GLFW_FALSE);
		glUniformMatrix4fv(slotShaderUniforms[3], 1, false, &(getTransform())[0][0]);
		glUniform3fv(slotShaderUniforms[4], 1, this->color); //Needs to add slotColor feature.
		glUniform1i(slotShaderUniforms[5], slotTexture ? true : false);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, slotTexture);

		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
	}
	void AQ_CompBoxInventory2D::disable(bool disable) {
		AQ_IHoverClick::disable(disable);
	}
	void AQ_CompBoxInventory2D::transformReset() {
		AQ_CompSimpleBox2D::transformReset();
	}
	void AQ_CompBoxInventory2D::transformRotate(glm::vec3 rotateVector, float angle) {
		AQ_CompSimpleBox2D::transformRotate(rotateVector, angle);
	}
	void AQ_CompBoxInventory2D::transformTranslate(glm::vec3 translateVector) {
		AQ_CompSimpleBox2D::transformTranslate(translateVector);
	}
	void AQ_CompBoxInventory2D::transformScale(glm::vec3 scaleVector) {
		AQ_CompSimpleBox2D::transformScale(scaleVector);
	}
	void AQ_CompBoxInventory2D::setTransform(glm::mat4 transform) {
		AQ_CompSimpleBox2D::setTransform(transform);
	}

	AQ_CompBoxInventory2D::~AQ_CompBoxInventory2D() {
		slotInstancingUsageCount--;
		if (!slotInstancingUsageCount) {
			if (slotInstancingVertexBuffers) {
				glDeleteVertexArrays(1, slotInstancingVertexBuffers);
				glDeleteBuffers(3, &slotInstancingVertexBuffers[1]);
				delete[] slotInstancingVertexBuffers;
			}
			if (slotInstancingShaderID) {
				glDeleteProgram(slotInstancingShaderID);
			}
			if (slotShaderUniforms) {
				delete[] slotShaderUniforms;
			}
		}
	}
}