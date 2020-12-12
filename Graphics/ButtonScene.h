#pragma once

#include "Scene.h"
#include "SphereScene.h"
#include "Button.h"
#include <vector>
#include <iostream>
#include "SceneController.h"
class ButtonScene : public Scene {
public:
	ButtonScene(GLFWwindow* window):Scene(window) {
		
	}
	virtual void init() {
		buttons.push_back(Button(0, 0.3, "./resources/textures/1.png", 0.2, 0.2));
		inButtonState.push_back(false);
		replacedScene.push_back(new SphereScene(this->getWindow()));
	}
	virtual void doCallBackFuncs(double xpos, double ypos) override {
		for (size_t i = 0; i < buttons.size(); i++) {
			inButtonState[i] = buttons[i].isInButton(xpos, ypos, 800, 600);
		}
	}

	virtual void doMouseButtonCallBack(int button, int action, int mods) override{
		for (size_t i = 0; i < buttons.size(); i++) if(inButtonState[i]) {
			if (action == GLFW_PRESS)
				switch (button) {
				case GLFW_MOUSE_BUTTON_LEFT:
					SceneController::getInstance()->replaceScene(replacedScene[i]);
					break;
				case GLFW_MOUSE_BUTTON_MIDDLE:
					break;
				case GLFW_MOUSE_BUTTON_RIGHT:
					break;

				}
		}
	}

	virtual void doProcessInput(GLFWwindow *window) override {}

	virtual void doDrawFunc() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto &b : buttons) {
			b.Draw();
		}
	}
private:
	std::vector<Button> buttons;
	std::vector<bool> inButtonState;
	std::vector<Scene*> replacedScene;
};