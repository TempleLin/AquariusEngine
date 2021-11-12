const char* testOutput {
//@TopSectionStart@
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"\n"
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"\n"
"uniform float windowWidth, windowHeight;\n"
"uniform bool keepAspectRatio;\n"
"uniform mat4 offsetMat;\n"
"\n"
"vec3 resultPos;\n"
"\n"
"void setAspectRatio();\n"
//@TopSectionEnd@
//@MainSectionStart@
"\n"
"void main() {\n"
"    setAspectRatio();\n"
"    gl_Position = offsetMat * vec4(resultPos, 1.0);\n"
"    ourColor = aColor;\n"
"    TexCoord = aTexCoord;\n"
"}\n"
//@MainSectionEnd@
//@BottomSectionStart@
"\n"
"void setAspectRatio() {\n"
"    if (keepAspectRatio) {\n"
"        if (windowWidth > windowHeight) {\n"
"            resultPos = vec3(windowHeight / windowWidth * aPos.x, aPos.y, aPos.z);\n"
"        } else if (windowWidth < windowHeight) {\n"
"            resultPos = vec3(aPos.x, windowWidth / windowHeight * aPos.y, aPos.z);\n"
"        } else {\n"
"            resultPos = aPos;\n"
"        }\n"
"    } else {\n"
"        resultPos = aPos;\n"
"    }\n"
"}\n"
//@BottomSectionEnd@
};