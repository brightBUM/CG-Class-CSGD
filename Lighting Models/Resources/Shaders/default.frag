#version 330 core
out vec4 FragColor;

//uniform - special keyword to pass data from cpu to gpu
uniform float time;
uniform sampler2D texSampler_0;
uniform sampler2D texSampler_1;
uniform float mixValue;
uniform vec3 objectColor;
in vec2 TexCoords;
in vec3 Normal;

uniform float ambientValue;
uniform vec3 lightPos;
uniform vec3 lightCol;
void main()
{
    //    vec4 texValue = texture(texSampler_0,TexCoords);

    //phong lighting = ambient +diffuse + specular

    //ambient light 
    vec3 ambient = lightCol*ambientValue;

    FragColor = vec4(ambient,1.0f);
    
} 