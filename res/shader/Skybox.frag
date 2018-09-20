#version 330 

uniform samplerCube _cubeTexture;

in vec3 _vsTexCoord;

out vec4 FragColor;

void main()
{
    FragColor = texture(_cubeTexture, _vsTexCoord);
}