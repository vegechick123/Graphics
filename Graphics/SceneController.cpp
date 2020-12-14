  #include "SceneController.h"

void SceneController::Do() {
	if(now != nullptr)
		now->doDrawFunc();
}

void SceneController::init() {
	glfwSetCursorPosCallback(now->getWindow(), cursorCallback);
	//glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(now->getWindow(), mouseCallback);
}

void SceneController::cursorCallback(GLFWwindow* window, double xpos, double ypos) {
	auto now = SceneController::getInstance()->getNow();
	if (now) {
		now->doCallBackFuncs(xpos, ypos);
	}
}
void SceneController::mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	auto now = SceneController::getInstance()->getNow();
	if (now) {
		now->doMouseButtonCallBack(button, action, mods);
	}
}
void SceneController::replaceScene(Scene* scene) {
	now = scene;
	if(now != nullptr)
		now->init();
	this->init();
}