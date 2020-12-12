#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using glm::vec3;
using glm::mat4;
class Transform
{
public :
	Transform* parent;
	vec3 position;
	vec3 rotation;
	vec3 scale;
	mat4 getModelMatrix();
	Transform(vec3 position = vec3(0, 0, 0), vec3 rotation = vec3(0, 0, 0), vec3 scale = vec3(1, 1, 1));

};

