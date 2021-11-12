#include "shaderHeaderConvert.hpp"
#include <fstream>
#include <iostream>


ShaderStrBuffer shaderToString(std::string shaderPath) {
	std::ifstream ifstream(shaderPath);
	ShaderStrBuffer strsBuffer;
	int shaderStrBufferIndex{ 0 };
	if (ifstream.is_open()) {
		while (ifstream) {
			std::string tempBuffer;
			std::getline(ifstream, tempBuffer);
			if (tempBuffer == "//@TopSectionStart@") {
				continue;
			} else if (tempBuffer == "//@TopSectionEnd@") {
				shaderStrBufferIndex++;
				continue;
			} else if (tempBuffer == "//@MainSectionStart@") {
				continue;
			} else if (tempBuffer == "//@MainSectionEnd@") {
				shaderStrBufferIndex++;
				continue;
			} else if (tempBuffer == "//@BottomSectionStart@") {
				continue;
			} else if (tempBuffer == "//@BottomSectionEnd@") {
				shaderStrBufferIndex++;
				continue;
			}
			strsBuffer.topMainBottom[shaderStrBufferIndex].append(tempBuffer);
			strsBuffer.topMainBottom[shaderStrBufferIndex].append("\n");
		}
	} else {
		std::cout << "Shader path specified doesn't exist.\n";
	}
	ifstream.close();
	return strsBuffer;
}

void stringToShader(ShaderStrBuffer strsBuffer) {

}

void stringToHeader(ShaderStrBuffer strsBuffer) {

}