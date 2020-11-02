#include "RenderObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Render\PointLight.h"
std::list<RenderObject*> RenderObject::list;
RenderObject* RenderObject::CreateRenderObject(MeshRenderer* meshRenderer, Material* _material)
{
	RenderObject* result = new RenderObject(meshRenderer, _material);
	list.push_back(result);
	return result;
}

void RenderObject::DrawAll(Camera camera)
{
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	
	for (RenderObject* renderObject : list)
	{
		renderObject->material->use();
		glm::mat4 model= renderObject->transform.getModelMatrix();

		renderObject->material->setMat4("projection", projection);
		renderObject->material->setMat4("view", view);
		renderObject->material->setMat4("model", model);

		Pointlight::ApplyAllLight(renderObject->material);
		renderObject->renderer->Draw(*(renderObject->material));
	}
}

RenderObject::RenderObject(MeshRenderer* meshRenderer, Material* _material)
{
	renderer = meshRenderer;
	material = _material;
}
RenderObject::~RenderObject()
{

}
void RenderObject::DestoryRenderObject(RenderObject* target)
{
	list.remove(target);
	delete target;
}