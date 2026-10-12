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
    vec4 texValue_0 = texture(texSampler_0,3.0f*TexCoords);
    vec4 texValue_1 = texture(texSampler_1,3.0f*TexCoords);
//    vec3 objectColor = vec3(0.5f,1.0f,0.0f);
    FragColor = mix(texValue_0,texValue_1,mixValue); 
//    FragColor = vec4(texValue_1.rgb,1.0f);
    
} 