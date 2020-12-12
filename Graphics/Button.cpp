#include "Button.h"
#include "stb_image.h"
#include "SceneController.h"

Button::Button(float x, float y, std::string filename, float scaleX, float scaleY)
	:x(x), y(y), scaleX(scaleX), scaleY(scaleY){
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


	// load and create a texture 
	// -------------------------
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

Button::Button(float x, float y, std::string beforeClick, std::string afterClick, float scaleX, float scaleY) {
	//gugugu
	Button(x, y, beforeClick, scaleX, scaleY);
}

void Button::Draw() {
	// bind Texture
	glBindTexture(GL_TEXTURE_2D, textureID);

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