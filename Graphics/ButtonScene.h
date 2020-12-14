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
		buttons.push_back(Button(0, 0.3, "./resources/textures/1.png", "./resources/textures/2.png", 0.2, 0.2));
		inButtonState.push_back(ButtonState::IDLE);
		replacedScene.push_back(new SphereScene(this->getWindow()));
	}
	virtual void doCallBackFuncs(double xpos, double ypos) override {
		for (size_t i = 0; i < buttons.size(); i++) {
			if (inButtonState[i] == ButtonState::IDLE && 
				buttons[i].isInButton(xpos, ypos, 800, 600)) {
				inButtonState[i] = ButtonState::INBOX;
			}

			if (inButtonState[i] == ButtonState::INBOX &&
				buttons[i].isInButton(xpos, ypos, 800, 600) == false) {
				inButtonState[i] = ButtonState::IDLE;
			}
		}
	}

	virtual void doMouseButtonCallBack(int button, int action, int mods) override{
		static bool isLastFramePressed = false;
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (action == GLFW_PRESS) {
				for (size_t i = 0; i < buttons.size(); i++) {
					if (inButtonState[i] == ButtonState::INBOX) {
						inButtonState[i] = ButtonState::PRESSED;
						buttons[i].setPressed(true);
					}
				}
			}
			else if (action == GLFW_RELEASE) {
				for (size_t i = 0; i < buttons.size(); i++) {
					if (inButtonState[i] == ButtonState::PRESSED) {
						inButtonState[i] = ButtonState::ACTIVATE;
						SceneController::getInstance()->replaceScene(replacedScene[i]);
						inButtonState[i] = ButtonState::IDLE;
						buttons[i].setPressed(false);
					}
				}
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
	enum ButtonState {
		IDLE,
		INBOX,
		PRESSED,
		ACTIVATE
	};
	std::vector<Button> buttons;
	std::vector<ButtonState> inButtonState;
	std::vector<Scene*> replacedScene;

};