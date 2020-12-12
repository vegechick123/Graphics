#include"DirectionLight.h"

DirectionLight::DirectionLight()
{
	direction =vec3(-1, -1, -1);
	intensity = 1;
} 

DirectionLight::~DirectionLight()
{
}

void DirectionLight::SetMaterialLight(Material* material, int index)
{
	std::string t;
	t += "directionLight.";
	material->setVec3(t + "direction", direction);
	material->setVec3(t + "color", color);
	material->setFloat(t + "intensity", intensity);
}
