#pragma once
#include <string>

/*
* @Shader files will be devided into three components, top/main/bottom.
*/
class ShaderStrBuffer {
public:
	std::string topMainBottom[3];
};

ShaderStrBuffer shaderToString(std::string shaderPath);
void stringToShader(const ShaderStrBuffer& strsBuffer, std::string shaderFileName);
void stringToHeader(const ShaderStrBuffer& strsBuffer, std::string headerFileName);