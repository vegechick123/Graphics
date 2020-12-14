#include "Button.h"
#include "stb_image.h"
#include "SceneController.h"

static unsigned int TextureFromFile(const char *filename) {

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(filename, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << filename << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

Button::Button(float x, float y, std::string filename, float scaleX, float scaleY)
	:x(x), y(y), scaleX(scaleX), scaleY(scaleY){
	pressed = false;
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // colors           // texture coords
		 x+scaleX,  y+scaleY, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 x+scaleX, y-scaleY, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		x-scaleX, y-scaleY, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		x-scaleX,  y+scaleY, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	shader = new Material("textures.vs", "textures.fs");
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	textureID = TextureFromFile(filename.c_str());
}

Button::Button(float x, float y, std::string beforeClick, std::string afterClick, float scaleX, float scaleY)
	:Button(x, y, beforeClick, scaleX, scaleY) {
	
	textureIDPressed = TextureFromFile(afterClick.c_str());
}

void Button::setPressed(bool b) {
	pressed = b;
}

void Button::Draw() {
	// bind Texture
	glActiveTexture(GL_TEXTURE0);
	
	if (pressed) {
		glUniform1i(glGetUniformLocation(shader->ID, "texture1"), 0);
		glBindTexture(GL_TEXTURE_2D, textureIDPressed);
	}
	else {
		glUniform1i(glGetUniformLocation(shader->ID, "texture1"), 0);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	
	//glBindTexture(GL_TEXTURE_2D, textureID);

	// render container
	shader->use();
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

bool Button::isInButton(double xpos, double ypos, double width, double height) {
	double midX = width / 2, midY = height / 2;
	double rectMidX = midX * (1 - x), rectMidY = midY * (1 - y);
	double halfLenX = width * scaleX / 2, halfLenY = height * scaleY / 2;
	return rectMidX - halfLenX <= xpos && xpos <= rectMidX + halfLenX && rectMidY - halfLenY <= ypos && ypos <= rectMidY + halfLenY;
}