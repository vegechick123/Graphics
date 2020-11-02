#pragma once
#include "Render\Transform.h"
#include "Render\MeshRenderer.h"
#include <learnopengl\camera.h>
#include <list>
#include<vector>
class RenderObject
{
	static std::list<RenderObject*> list;
public:
	Transform transform;
	MeshRenderer renderer;
	Material* material;
	static RenderObject* CreateRenderObject(string const& meshPath, Material* material, bool gamma = false);
	static void DrawAll(Camera camera);
	void DestoryRenderObject(RenderObject* target);
private:
	RenderObject(string const& meshPath, Material* material, bool gamma = false);
	~RenderObject();
};

