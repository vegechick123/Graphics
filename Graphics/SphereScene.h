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
		Material ourShader("resources/shader/1.model_loading.vert", "resources/shader/1.model_loading.frag");

		// load models
		// -----------
		//MeshRenderer ourModel("resources/sz.obj");
		MeshRenderer sphere("resources/sphere.obj");
		RenderObject* targetTest = RenderObject::CreateRenderObject(&sphere, &ourShader);
		//targetTest->transform.scale = vec3(0.1, 0.1, 0.1);
		//targetTest->transform.position.y = 1;
		lights = new Pointlight*[potLightNum];
		//Pointlight* lights[potLightNum];
		DirectionLight* dirlight = DirectionLight::CreateLight();
		dirlight->intensity = 1;
		//dirlight->color = vec3(1, 0, 0);
		for (int i = 0; i < potLightNum; i++)
		{
			lights[i] = Pointlight::CreateLight();
			RenderObject* lightSphere = RenderObject::CreateRenderObject(&sphere, &ourShader);
			lightSphere->transform.scale = vec3(0.1, 0.1, 0.1);
			lightSphere->transform.parent = &lights[i]->transform;
		}
		lights[0]->color = vec3(1, 0, 0);
		lights[1]->color = vec3(0, 1, 0);
		lights[2]->color = vec3(0, 0, 1);

		lights[0]->transform.position = vec3(2, -0.5, -0.5);
		lights[1]->transform.position = vec3(0, 2, 0);
		lights[2]->transform.position = vec3(0, 0, 2);
	}

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


		//äÖÈ¾Ö÷Ñ­»·
		for (int i = 0; i < 3; i++)
		{
			float cnt = currentFrame + 3.1415926*i * 2 / 3;
			lights[i]->transform.position = vec3(2 * sin(cnt), 0, 2 * cos(cnt));
		}
		cout << "Drawing\n";
		RenderObject::DrawAll(camera);

	}
private:
	Camera camera;
	Pointlight** lights;
	float deltaTime;
};