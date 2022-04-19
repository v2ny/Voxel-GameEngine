#version 330 core

out vec4 FragmentColor;

in vec3 color;

void main()
{
    FragmentColor = vec4(color, 1.0f);
}