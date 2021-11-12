//@TopSectionStart@
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform float windowWidth, windowHeight;
uniform bool keepAspectRatio;
uniform mat4 offsetMat;

vec3 resultPos;

void setAspectRatio();

//@TopSectionEnd@
//@MainSectionStart@

void main() {
    setAspectRatio();
    gl_Position = offsetMat * vec4(resultPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}

//@MainSectionEnd@
//@BottomSectionStart@

void setAspectRatio() {
    if (keepAspectRatio) {
        if (windowWidth > windowHeight) {
            resultPos = vec3(windowHeight / windowWidth * aPos.x, aPos.y, aPos.z);
        } else if (windowWidth < windowHeight) {
            resultPos = vec3(aPos.x, windowWidth / windowHeight * aPos.y, aPos.z);
        } else {
            resultPos = aPos;
        }
    } else {
        resultPos = aPos;
    }
}

//@BottomSectionEnd@
