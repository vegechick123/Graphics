#include "RenderObject.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
std::list<RenderObject*> RenderObject::list;
RenderObject* RenderObject::CreateRenderObject(string const& meshPath, Material* material,bool gamma)
{
	RenderObject* result = new RenderObject(meshPath, material,gamma);
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
		renderObject->renderer.Draw(*(renderObject->material));
	}
}

RenderObject::RenderObject(string const& meshPath, Material* _material, bool gamma):renderer(meshPath, gamma)
{
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