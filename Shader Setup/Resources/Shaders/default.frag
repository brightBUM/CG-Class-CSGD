#version 330 core
out vec4 FragColor;
//uniform - special keyword to pass data from cpu to gpu
uniform float time;
in vec3 Color;

void main()
{
    vec3 objectColor = vec3(0.5f,1.0f,0.0f);
    FragColor = vec4(objectColor, 1.0f);
    
} 