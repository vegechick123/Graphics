#pragma once
#include <glm\glm.hpp>
#include "Transform.h"
#include "Material.h"
#include <list>
template <typename T>
class LightSource
{
    static std::list<T*> list;
public:

    glm::vec3 color;
    virtual void SetMaterialLight(Material* material, int index = 0)=0;
};

