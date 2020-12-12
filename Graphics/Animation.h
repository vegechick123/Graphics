#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using glm::vec3;
template<typename T>
class Animation
{
public:
	T(*GetValueAtSpeceficTime)(float);
	Animation(T(*func)(float), T* target);
	T* target;
	float currentTime;
	void Update(float deltaTime);
	

	void Play(float startTime=0);

};

template<typename T>
inline void Animation<T>::Update(float deltaTime)
{
	currentTime += deltaTime;
	*target = GetValueAtSpeceficTime(currentTime);
}

template<typename T>
inline Animation<T>::Animation(T(*func)(float) , T* target)
{
	currentTime = -1;
	GetValueAtSpeceficTime=func;
	this->target = target;
}

template<typename T>
inline void Animation<T>::Play(float startTime)
{
	currentTime = startTime;
}

