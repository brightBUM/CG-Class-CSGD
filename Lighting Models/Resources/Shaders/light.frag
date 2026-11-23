#version 330 core
out vec4 FragColor;

//uniform - special keyword to pass data from cpu to gpu

uniform vec3 lightCol;
in vec2 TexCoords;

void main()
{
    FragColor = vec4(lightCol,1.0f);
    
} 