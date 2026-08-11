#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

namespace Utils {
	// Rendering Methods
	GLuint createShaderProgram(void);
	string readShaderSource(const char* filePath);

	// Texture-Handling Methods
	GLuint loadtexture(const char* textureImageFilePath);

	// Error Handling Methods
	void printShaderLog(GLuint shader);
	void printProgramLog(int program);
	bool checkOpenGLError(void);
}