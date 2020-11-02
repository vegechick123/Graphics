#version 330 core
out vec4 FragColor;
struct PointLight {
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;	
};
in vec2 TexCoords;
in vec3 fragPos;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform sampler2D texture_diffuse1;
uniform int lightNum;
vec3 CalcPointLight(PointLight light,vec3 fragPos)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    return attenuation*light.color;
}

void main()
{   
    vec3 diffuse = texture(texture_diffuse1, TexCoords).xyz;

    vec3 finalcolor = vec3(0,0,0);

    for(int i =0;i<lightNum;i ++)
    {
        finalcolor += CalcPointLight(pointLights[i],fragPos)*diffuse;
    }
    FragColor = vec4(finalcolor,1);
    //FragColor = vec4(fragPos,1);
    //FragColor = texture(texture_diffuse1, TexCoords);
}

