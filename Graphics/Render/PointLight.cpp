#include"PointLight.h"
#include <string>
Pointlight::Pointlight()
{
	constant = 1;
	linear = 1;
	quadratic = 1;
}

Pointlight::~Pointlight()
{
}

void Pointlight::SetMaterialLight(Material* material, int index)
{

	std::string t;
	t += "pointLights[";
	t += '0' + index;
	t += "].";
	material->setVec3(t + "position",transform.position);
	material->setVec3(t + "color", color);
	material->setFloat(t + "constant", constant);
	material->setFloat(t + "linear", linear);
	material->setFloat(t + "quadratic", quadratic);
}
