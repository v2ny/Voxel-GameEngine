#version 330 core

out vec4 FragmentColor;

uniform vec4 lightColor;

void main()
{
    FragmentColor = lightColor;
}