#version 330 core
out vec4 FragColor;

//uniform - special keyword to pass data from cpu to gpu
uniform float time;
uniform sampler2D texSampler_0;
uniform sampler2D texSampler_1;
uniform float mixValue;
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform float ambientValue;
uniform vec3 lightPos;
uniform vec3 lightCol;
void main()
{
    //    vec4 texValue = texture(texSampler_0,TexCoords);

    //phong lighting = ambient +diffuse + specular

    //ambient light 
    vec3 ambient = lightCol*ambientValue;

    //diffuse light  - dot product b/w normal and lightDir
    vec3 A = normalize(Normal);
    vec3 B = normalize(lightPos-FragPos);

    float dotValue = dot(A,B);
    float diffuseValue = max(dotValue,0.0f);
    vec3 diffuse = diffuseValue*lightCol;

    //lambertian diffuse - ambient+diffuse
    FragColor = vec4(ambient+diffuse,1.0f);  
    
} 