#include"PointLight.h"
#include <string>
#include<iostream>
Pointlight::Pointlight()
{
	/*constant = 100;
	linear = 100;
	quadratic = 100;*/
	constant = 0.01;
	linear = 0.1;
	quadratic = 0.1;
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
	material->setVec3(t + "position",transform.getWorldPosition());
	material->setVec3(t + "color", color);
	material->setFloat(t + "constant", constant);
	material->setFloat(t + "linear", linear);
	material->setFloat(t + "quadratic", quadratic);
}
