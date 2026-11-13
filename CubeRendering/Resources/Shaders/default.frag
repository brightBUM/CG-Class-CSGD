#version 330 core
out vec4 FragColor;

//uniform - special keyword to pass data from cpu to gpu
uniform float time;
uniform sampler2D texSampler_0;
uniform sampler2D texSampler_1;
uniform float mixValue;
uniform vec3 objectColor;
in vec2 TexCoords;

void main()
{
    vec4 texValue = texture(texSampler_0,TexCoords);
    FragColor = vec4(texValue);
    
} 