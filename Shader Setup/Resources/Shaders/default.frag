#version 330 core
out vec4 FragColor;
//uniform - special keyword to pass data from cpu to gpu
uniform float time;
in vec3 Color;

void main()
{
    FragColor = vec4(Color, 1.0f);
    
} 