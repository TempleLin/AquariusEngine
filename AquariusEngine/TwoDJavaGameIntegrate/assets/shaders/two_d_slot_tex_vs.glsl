#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 aOffset;

out vec3 ourColor;
out vec2 TexCoord;

uniform float windowWidth, windowHeight;
uniform bool keepAspectRatio;
uniform mat4 offsetMat;
uniform vec3 color;

vec3 resultPos;

void setAspectRatio();

void main() {
	setAspectRatio();
	gl_Position = offsetMat * vec4(resultPos, 1.0);
	ourColor = aColor;
	ourColor *= color;
	TexCoord = aTexCoord;
}

void setAspectRatio() {
	if (keepAspectRatio) {
		if (windowWidth > windowHeight) {
			resultPos = vec3(windowHeight / windowWidth * (aPos.x + aOffset.x), aPos.y + aOffset.y, aPos.z);
		} else if (windowWidth < windowHeight) {
			resultPos = vec3(aPos.x + aOffset.x, windowWidth / windowHeight * (aPos.y + aOffset.y), aPos.z);
		} else {
			resultPos = aPos;
			resultPos.xy += aOffset;
		}
	} else {
		resultPos = aPos;
		resultPos.xy += aOffset;
	}
}