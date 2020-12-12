#pragma once
#include"LightSource.h"
class Pointlight:public LightSource<Pointlight>
{
public:
	float constant;
	float linear;
	float quadratic;
	Pointlight();
	~Pointlight();
	void SetMaterialLight(Material* material, int index = 0) override;
private:

};

