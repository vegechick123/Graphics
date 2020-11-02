#include "Transform.h"

mat4 Transform::getModelMatrix()
{
	mat4 model = mat4(1.0f);
	model = glm::translate(mat4(1.0f), position); // translate it down so it's at the center of the scene
	model = glm::rotate(model, rotation.x, vec3(1, 0, 0));
	model = glm::rotate(model, rotation.y, vec3(0, 1, 0));
	model = glm::rotate(model, rotation.z, vec3(0, 0, 1));
	model = glm::scale(model, scale);
	return model;
}

Transform::Transform(vec3 position, vec3 rotation, vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
}
