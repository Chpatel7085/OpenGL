#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<iostream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<fstream>
#include<sstream>
#include<streambuf>
#include<string>


class Shader {
public :
	unsigned int id;
	//Constructor
	Shader(const char* vertexSHaderPath, const char* fragmentShaderPath);
	void activate();

	//utility functions
	std::string loadShaderSrc(const char* filepath);
	GLuint compileShader(const char* filepath, GLenum type);

	//uniform functions
	void setMat4(const std::string& name, glm::mat4 val);
	void setInt(const std::string& name, int value);

};
#endif
