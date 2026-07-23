#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const string& fragmentPath) {
	// Read the shader source code from files
	string vertexCode = readShaderSource(vertexPath);
	string fragmentCode = readShaderSource(fragmentPath.c_str());
	// Compile the shaders
	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode.c_str(), vertexPath);
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str(), fragmentPath.c_str());
	// Create the shader program and link the shaders
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);
	// Check for linking errors
	checkLinkErrors(programID);
	// Delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(programID);
}

string Shader::readShaderSource(const char* filePath) const {
	ifstream shaderFile;
	shaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	try {
		shaderFile.open(filePath);
		stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		return shaderStream.str();
	}
	catch (ifstream::failure& e) {
		cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << filePath << endl;
		return "";
	}
}

GLuint Shader::compileShader(GLenum shaderType, const char* source, const char* debugName) {
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	// Check for compilation errors
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar infoLog[1024]; // AI says 512 not 1024, look into this
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << debugName << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
	}
	return shader;
}

void Shader::checkLinkErrors(GLuint program) const {
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog[1024];
		glGetProgramInfoLog(program, 1024, NULL, infoLog);
		cerr << "ERROR::PROGRAM_LINKING_ERROR\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
	}
}

void Shader::use() const {
	glUseProgram(programID);
}

void Shader::setMat4(const string& name, const glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setVec3(const string& name, const glm::vec3& vec) const {
	glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setFloat(const string& name, float value) const {
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void shader::setInt(const string& name, int value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}