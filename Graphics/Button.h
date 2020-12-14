#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Render/Material.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Button {
public:
	unsigned int VAO;
	Button(float x, float y, std::string filename, float scaleX, float scaleY);
	Button(float x, float y, std::string beforeClick, std::string afterClick, float scaleX, float scaleY);
	bool isInButton(double xpos, double ypos, double width, double height);
	void Draw();
	void setPressed(bool);
private:
	unsigned int textureID, textureIDPressed;
	bool pressed;
	Material* shader;
	unsigned int VBO, EBO;
	float x, y, scaleX, scaleY;
};