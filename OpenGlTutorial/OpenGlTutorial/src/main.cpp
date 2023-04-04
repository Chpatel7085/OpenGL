#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <stb/stb_image.h>
#include<fstream>
#include<sstream>
#include<streambuf>
#include<string>
#include "Shader.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
//string loadShaderSrc(const char* filename);//to load the shaders files, i.e, vertex and fragments

unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;
float x, y, z;


int main() {
	cout << "Hello World" << endl;

	int success;
	char infoLog[512];

	//initialize glfw
	glfwInit();

	//open GLFW version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);


	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//it uses the modern profile of glfw

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGGL", NULL, NULL);

	if (window == NULL) { //window not created
		cout << "Could not create window" << endl;
		glfwTerminate();
		return -1;
	}
	//make the glfw to focus on this window
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to Initialize GLAD" << endl;
		glfwTerminate();
		return -1;
	}

	// render the window
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	//for dynamically resizing the window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*
	   shaders
	*/

	//Setting the z buffer or depth testing

	glEnable(GL_DEPTH_TEST);

	Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");

	//vertex array
	//NDC - > Normalized device Coordinates
	float vertices[] = {
     //position           //texCoord
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = {
		0 , 1, 2,//first triangle
		3, 1, 2 //second triangle
	};

	//Vertex Array Object(VAO) will contain pointers to the data buffer and these
	//data buffer will be stored in Vertex buffer object(VBO)
	//EBO(Element Array Buffer) it helps us to eclude the common vertices of the array

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);


	//bind VAO
	glBindVertexArray(VAO);

	//bind VBO 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//GL_STATIC_DRAW this tells the openGL that we are not going to modified the data much
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//set attribute pointer

	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	////colors
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	//texture coordinate
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Textures 
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	//wraps the texture along x direction (s) and y direction (t)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//openGl decide which pixel to display or map 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//load image
	//nChannels - >RGB / RG/ R etc
	int width, height, nChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("assets/image2.png", &width, &height, &nChannels, 0);


	//set data into the Texture
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//more efficieny
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "Failed to load the data" << endl;
	}
	stbi_image_free(data);

	//second texture
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	data = stbi_load("assets/image1.png", &width, &height, &nChannels, 0);

	if (data) {
		//png have one more component that is alpha 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//more efficieny
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		cout << "Failed to load the data" << endl;
	}
	stbi_image_free(data);

	shader.activate();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	x = 0.0f, y = 0.0f, z = 3.0f;


	

	while (!glfwWindowShouldClose(window)) {
		//process input window
		processInput(window);

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//activating the texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
				
		
		//draw shapes

		//create the camera view 

		glm::mat4 model = glm::mat4(1.0f);//for translating bodies from local to world space
		glm::mat4 view = glm::mat4(1.0f);//creating that camera view effect
		glm::mat4 projection = glm::mat4(1.0f);//for creating the perspective of a user of what can they see

		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.f), glm::vec3(0.5f));
		view = glm::translate(view, glm::vec3(-x, -y, -z));
		projection = glm::perspective(glm::radians(20.f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		glBindVertexArray(VAO);
		
		//draw the first triangle
		shader.activate();
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);
		
		//glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		////draw the second triangle
		//glBindVertexArray(0);
		
		//sent new frames to window
		glfwSwapBuffers(window);

		//tells if any events triggers or not like keyword press, mouse click
		glfwPollEvents();
		
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;

}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

//string loadShaderSrc(const char* filename) {
//	ifstream file;
//	stringstream buf;// to read the data of the file
//	string ret = "";//placeholder for the return variable
//	
//	file.open(filename);
//
//	if (file.is_open()) {
//		buf << file.rdbuf();//read buffer/ piping to the string buffer
//		ret = buf.str();
//		
//	}
//	else {
//		cout << "Could not open " << filename << endl;
//	}
//	file.close();
//	return ret;
//}