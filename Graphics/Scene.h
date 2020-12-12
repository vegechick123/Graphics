#pragma once

#include "glfw/glfw3.h"
#include <vector>

typedef void mouse_callback(double , double);
typedef void draw_func();
class Scene {
public:
	Scene() {}
	Scene(GLFWwindow* window) :window(window) {}
	virtual void doCallBackFuncs(double x, double y) = 0;
	virtual void doMouseButtonCallBack(int button, int action, int mods) = 0;
	virtual void doDrawFunc() = 0;
	virtual void doProcessInput(GLFWwindow* window) = 0;
	virtual void init() = 0;
	GLFWwindow* getWindow() {
		return window;
	}
private:
	GLFWwindow* window;
};