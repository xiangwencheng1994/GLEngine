#version 330 

uniform mat4 _mvp;

in vec3 _position;

out vec3 _vsTexCoord;

void main()
{
    vec4 pos = _mvp * vec4(_position, 1);
    gl_Position = pos.xyww;
    _vsTexCoord = _position;
}