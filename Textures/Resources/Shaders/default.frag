#version 330 core
out vec4 FragColor;

//uniform - special keyword to pass data from cpu to gpu
uniform float time;
uniform sampler2D texSampler;

in vec3 Color;
in vec2 TexCoords;

void main()
{
    //textures - 1st params - texture object id via a sampler2D
    //texutures - 2nd params - texture co ordinates
    vec4 texValue = texture(texSampler,TexCoords);
//    vec3 objectColor = vec3(0.5f,1.0f,0.0f);
    FragColor = vec4(texValue);
    
} 