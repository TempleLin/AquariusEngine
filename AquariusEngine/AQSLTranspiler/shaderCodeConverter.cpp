#include "shaderCodeConverter.hpp"
#include <fstream>
#include <sstream>
#include <iostream>


ShaderStrBuffer shaderToString(std::string shaderPath) {
	std::ifstream ifstream(shaderPath);
	ShaderStrBuffer strsBuffer;
	std::stringstream strstream;
	int shaderStrBufferIndex{ 0 };
	if (ifstream.is_open()) {
		while (ifstream) {
			std::string tempBuffer;
			std::getline(ifstream, tempBuffer);
			if (tempBuffer == "//@TopSectionStart@") {
				continue;
			} else if (tempBuffer == "//@TopSectionEnd@") {
				strsBuffer.topMainBottom[shaderStrBufferIndex] = strstream.str();
				strstream.str("");
				shaderStrBufferIndex++;
				continue;
			} else if (tempBuffer == "//@MainSectionStart@") {
				continue;
			} else if (tempBuffer == "//@MainSectionEnd@") {
				strsBuffer.topMainBottom[shaderStrBufferIndex] = strstream.str();
				strstream.str("");
				shaderStrBufferIndex++;
				continue;
			} else if (tempBuffer == "//@BottomSectionStart@") {
				continue;
			} else if (tempBuffer == "//@BottomSectionEnd@") {
				strsBuffer.topMainBottom[shaderStrBufferIndex] = strstream.str();
				strstream.str("");
				shaderStrBufferIndex++;
				continue;
			}
			strstream << tempBuffer;
			strstream << "\n";
		}
	} else {
		std::cout << "Shader path specified doesn't exist.\n";
	}
	ifstream.close();
	return strsBuffer;
}

void stringToShader(const ShaderStrBuffer& strsBuffer, std::string shaderFileName) {
	std::ofstream ofstream(shaderFileName, std::fstream::out);
	if (ofstream.is_open()) {
		ofstream << "//@TopSectionStart@\n";
		ofstream << strsBuffer.topMainBottom[0] << "\n";
		ofstream << "//@TopSectionEnd@\n";

		ofstream << "//@MainSectionStart@\n";
		ofstream << strsBuffer.topMainBottom[1] << "\n";
		ofstream << "//@MainSectionEnd@\n";

		ofstream << "//@BottomSectionStart@\n";
		ofstream << strsBuffer.topMainBottom[2] << "\n";
		ofstream << "//@BottomSectionEnd@\n";
	} else {
		std::cout << "Something went wrong in outputting string buffers to shader file.\n";
	}
	ofstream.close();
}

void stringToHeader(const ShaderStrBuffer& strsBuffer, std::string headerFileName, std::string varName) {
	std::stringstream strstream;
	std::ofstream ofstream(headerFileName, std::fstream::out);
	std::string tempStr;
	if (ofstream.is_open()) {
		ofstream << "const char* " << varName << " {\n";
		ofstream << "//@TopSectionStart@\n";
		strstream << strsBuffer.topMainBottom[0];
		if (!strsBuffer.topMainBottom[0].empty()) {
			while (std::getline(strstream, tempStr, '\n')) {
				ofstream << "\"" << tempStr << "\\n\"\n";
			}
		}
		ofstream << "//@TopSectionEnd@\n";

		ofstream << "//@MainSectionStart@\n";
		strstream.clear();
		strstream << strsBuffer.topMainBottom[1];
		if (!strsBuffer.topMainBottom[1].empty()) {
			while (std::getline(strstream, tempStr, '\n')) {
				ofstream << "\"" << tempStr << "\\n\"\n";
			}
		}
		ofstream << "//@MainSectionEnd@\n";

		ofstream << "//@BottomSectionStart@\n";
		strstream.clear();
		strstream << strsBuffer.topMainBottom[2];
		if (!strsBuffer.topMainBottom[2].empty()) {
			while (std::getline(strstream, tempStr, '\n')) {
				ofstream << "\"" << tempStr << "\\n\"\n";
			}
		}
		ofstream << "//@BottomSectionEnd@\n" << "};";
		ofstream.close();
	}
}