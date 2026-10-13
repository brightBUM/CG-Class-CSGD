#version 330 core
out vec4 FragColor;

//uniform - special keyword to pass data from cpu to gpu
uniform float time;
uniform sampler2D texSampler_0;
uniform sampler2D texSampler_1;
uniform float mixValue;
in vec3 Color;
in vec2 TexCoords;

void main()
{
    //textures - 1st params - texture object id via a sampler2D
    //texutures - 2nd params - texture co ordinates
    vec2 uv = TexCoords;

    uv.x -= sin(time)*0.5f;

    vec4 texValue_0 = texture(texSampler_0,3.0f*uv);
    vec4 texValue_1 = texture(texSampler_1,3.0f*uv);
//    vec3 objectColor = vec3(0.5f,1.0f,0.0f);
    vec4 mixValue = mix(texValue_0,texValue_1,mixValue); 
    FragColor = mixValue;
    
} 