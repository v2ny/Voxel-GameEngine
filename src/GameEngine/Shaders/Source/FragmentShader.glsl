#version 330 core

out vec4 FragmentColor;

in vec3 color;

in vec2 texCoord;

uniform sampler2D tex0;


void main()
{
	FragmentColor = texture(tex0, texCoord);
}