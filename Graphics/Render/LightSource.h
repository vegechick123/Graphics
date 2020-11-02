#pragma once
#include <glm\glm.hpp>
#include "Transform.h"
#include "Material.h"
#include <list>
#include <string>
template <typename T>
class LightSource
{
protected:
    static std::list<LightSource*> list;

public:
    LightSource();
    Transform transform;
    glm::vec3 color;
    virtual void SetMaterialLight(Material* material, int index = 0)=0;
    static T* CreateLight();
    static void ApplyAllLight(Material* material);
    static void DestoryLight(T* t);

};
template<typename T>
std::list<LightSource<T>*> LightSource<T>::list;

template<typename T>
LightSource<T>::LightSource()
{
    transform = Transform();
    color = vec3(1, 1, 1);
}

template<typename T>
T* LightSource<T>::CreateLight()
{
    T* result = new T();
    list.push_back(result);
    return result;
}

template<typename T>
void LightSource<T>::ApplyAllLight(Material* material)
{
    int index = 0;
    material->setInt("lightNum", list.size());
    for(LightSource* lightSource : list)
    {
        lightSource->SetMaterialLight(material,index);
        index++;
    }
}

template<typename T>
void LightSource<T>::DestoryLight(T* t)
{
    list.remove(t);
    delete t;
    return;
}