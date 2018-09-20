#version 330 

uniform mat4 _mvp;

in vec3 _position;
in vec4 _color;

out vec4 _vsColor;

void main()
{
    gl_Position = _mvp * vec4(_position, 1);
    _vsColor = _color;
}