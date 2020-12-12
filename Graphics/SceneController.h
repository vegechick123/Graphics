#pragma once
#include "Scene.h"
#include <GLFW/glfw3.h>

class SceneController {
public:
	SceneController(Scene* s = nullptr) {
		now = s;
	}
	static SceneController* getInstance() {
		static SceneController* instance = new SceneController();
		return instance;
	}
	void Do();
	void replaceScene(Scene* scene);
	static void cursorCallback(GLFWwindow* , double, double);
	static void mouseCallback(GLFWwindow*, int, int, int);
	Scene* getNow() {
		return now;
	}
private:
	Scene* now;
	void init();
};