#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform bool useTexture;

void main()
{
    if (useTexture) {
        // @Multiply the texture by color mixes the RGB color and texture.
        FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    } else {
        FragColor = vec4(ourColor, 1.0);
    }

    if (FragColor.a == 0.f){
        discard;
    }
}