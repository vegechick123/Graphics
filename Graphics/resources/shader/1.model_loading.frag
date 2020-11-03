#version 330 core
out vec4 FragColor;
struct PointLight {
    vec3 position;
    vec3 color;

    float constant;
    float linear;
    float quadratic;	
};
struct DirectionLight {
    vec3 direction;
    vec3 color;
    float intensity;	
};
in vec2 TexCoords;
in vec3 fragPos;
in mat3 TBN;
#define NR_POINT_LIGHTS 4

uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform DirectionLight directionLight;
uniform int lightNum;
uniform vec3 viewPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;

const float PI = 3.14159265359;
vec3 CalcPointLight(PointLight light,vec3 fragPos)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    return attenuation*light.color;
}
vec3 CalcDirectionLight(DirectionLight light)
{
    // combine results
    return light.intensity*light.color;
}
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / max(denom, 0.001); // prevent divide by zero for roughness=0.0 and NdotH=1.0
}
// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}
// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
void main()
{   
    vec3 albedo = texture(texture_diffuse1, TexCoords).xyz;
    vec3 normal = texture(texture_normal1, TexCoords).rgb;
    vec3 ambient =vec3(0.2,0.2,0.2);
    float metallic=1;
    float roughness=0.4;
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo.rgb, metallic);
    normal = normalize(normal * 2.0 - 1.0);   
    normal = normalize(TBN * normal);

    vec3 viewDir= normalize(fragPos-viewPos);
    vec3 finalcolor = 0.7*ambient*albedo;

    for(int i =0;i<lightNum+1;i ++)
    {
        
        vec3 lightCol;
        if(i<lightNum)
            lightCol=CalcPointLight(pointLights[i],fragPos);
        else
            lightCol=CalcDirectionLight(directionLight);
        vec3 lightDir;
        if(i<lightNum)
            lightDir=normalize(fragPos-pointLights[i].position);
        else
            lightDir=normalize(directionLight.direction);

        vec3 halfDir=normalize(-lightDir-viewDir);
        float NDF = DistributionGGX(normal, halfDir, roughness);   
        float G   = GeometrySmith(normal, -viewDir, -lightDir, roughness);  
        vec3 F =fresnelSchlick(clamp(dot(halfDir, -viewDir), 0.0, 1.0), F0);
        vec3 nominator    = NDF * G * F; 
        float denominator = 4 * max(dot(normal, -viewDir), 0.0) * max(dot(normal, -lightDir), 0.0);
        vec3 specular = nominator / max(denominator, 0.001); // prevent divide by zero for NdotV=0.0 or NdotL=0.0
        // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals 
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;

        float NdotL = max(dot(normal, -lightDir), 0.0);     
        finalcolor += (kD*albedo.rgb/PI+ specular)*lightCol*NdotL;//1 *CalcPointLight(pointLights[i],fragPos)*albedo;
    }
    FragColor = vec4(finalcolor,1);
    //FragColor = vec4(fragPos,1);
    //FragColor = texture(texture_diffuse1, TexCoords);
}
