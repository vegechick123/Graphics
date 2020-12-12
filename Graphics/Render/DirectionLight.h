#pragma once
#include"LightSource.h"
class DirectionLight:public LightSource<DirectionLight>
{
public:
	vec3 direction;
	float intensity;
	DirectionLight();
	~DirectionLight();
	void SetMaterialLight(Material* material, int index = 0) override;
};

