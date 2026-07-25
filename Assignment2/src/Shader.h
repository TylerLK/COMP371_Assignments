#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>

using namespace std;

class Shader {

public:
	GLuint programID;

	// Constructor
	Shader(const char* vertexPath, const string& fragmentPath);
	// Destuctor
	~Shader();

	void use() const;

	// Setters
	void setMat4(const string& name, const glm::mat4& mat) const;
	void setVec3(const string& name, const glm::vec3& vec) const;
	void setFloat(const string& name, float value) const;
	void setInt(const string& name, int value) const;

private:
	string readShaderSource(const char* filePath) const; // read the file
	GLuint compileShader(GLenum shaderType, const char* source, const char* debugName); // compile the shader
	void checkLinkErrors(GLuint program) const; // check for linking errors
};
#endif