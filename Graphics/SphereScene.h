#pragma once

#include "Scene.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "learnopengl/camera.h"
#include "Render\MeshRenderer.h"
#include "Render\Material.h"
#include "Render\Transform.h"
#include "RenderObject.h"
#include "Render\PointLight.h"
#include "Render\DirectionLight.h"
#include "Animation.h"

#include <algorithm>
#include <vector>
#include <iostream>
class SphereScene : public Scene {
public:
	SphereScene(GLFWwindow* window) :Scene(window) {}
	virtual void doMouseButtonCallBack(int a, int b, int c) override {};
	virtual void init() {
		// tell GLFW to capture our mouse
		glfwSetInputMode(this->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glEnable(GL_DEPTH_TEST);
		int potLightNum = 3;
		camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
		Material *ourShader=new Material("resources/shader/1.model_loading.vert", "resources/shader/1.model_loading.frag");
		 
		// load models
		// -----------
		//MeshRenderer ourModel("resources/sz.obj");
		MeshRenderer *sphere=new MeshRenderer("resources/sphere.obj");
		RenderObject* targetTest = RenderObject::CreateRenderObject(sphere, ourShader);
		lights = new Pointlight*[potLightNum];
		//Pointlight* lights[potLightNum];
		DirectionLight* dirlight = DirectionLight::CreateLight();
		dirlight->intensity = 1;
		//dirlight->color = vec3(1, 0, 0);
		for (int i = 0; i < potLightNum; i++)
		{
			lights[i] = Pointlight::CreateLight();
			lights[i]->transform.parent = &targetTest->transform;
			RenderObject* lightSphere = RenderObject::CreateRenderObject(sphere, ourShader);
			lightSphere->transform.scale = vec3(0.1, 0.1, 0.1);
			lightSphere->transform.parent = &lights[i]->transform;
		}
		
		lights[0]->color = vec3(1, 0, 0);
		lights[1]->color = vec3(0, 1, 0);
		lights[2]->color = vec3(0, 0, 1);
		vec3(*circleFunc)(float) = [](float t) {return vec3(2 * sin(t), 0, 2 * cos(t)); };
		animations = new vector<Animation<vec3>*>;
		for (int i = 0; i < 3; i++)
		{
			Animation<vec3>* t = new Animation<vec3>(circleFunc, &(lights[i]->transform.position));
			t->Play(3.1415926 * i * 2 / 3);
			animations->push_back(t);
			
		}
		Animation<vec3>* EnterPositionAnimation = new Animation<vec3>([](float t) {
			return vec3(0,0,-5+0.3f*t); }, & (targetTest->transform.position));
		EnterPositionAnimation->Play();
		animations->push_back(EnterPositionAnimation);

		Animation<vec3>* EnterRotationAnimation = new Animation<vec3>([](float t) {
			return vec3(0, 0.3f*t,0); }, &(targetTest->transform.rotation));
		EnterRotationAnimation->Play();
		animations->push_back(EnterRotationAnimation);

	};

	virtual void doCallBackFuncs(double xpos, double ypos) override {
		static bool firstMouse = true;
		static float lastX = 0, lastY = 0;
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}
		// std::cout << xpos << ' ' << ypos << '\n';
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}

	virtual void doProcessInput(GLFWwindow * window) override {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, deltaTime);
	}

	virtual void doDrawFunc() {
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		static float lastFrame = 0;
		
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		this->doProcessInput(this->getWindow());

		for (int i = 0; i < animations->size(); i++)
		{
			(*animations)[i]->Update(deltaTime);
		}
		// cout << "Drawing\n";
		RenderObject::DrawAll(camera);

	}
private:
	Camera camera;
	Pointlight** lights;
	float deltaTime;
	vector<Animation<vec3>*>* animations;
};