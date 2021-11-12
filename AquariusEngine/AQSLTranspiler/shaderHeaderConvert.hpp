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
void stringToShader(ShaderStrBuffer strsBuffer);
void stringToHeader(ShaderStrBuffer strsBuffer);