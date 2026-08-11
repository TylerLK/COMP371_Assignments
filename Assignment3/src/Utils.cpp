#include <SOIL2.h>

#include <iostream>
#include <string>
#include <fstream>

#include "Utils.h"

using namespace std;

namespace Utils {
	// Creates a shader program and returns its ID
	GLuint createShaderProgram(void) {
		// Define error flags
		GLint vCompiled;
		GLint fCompiled;
		GLint linked;

		// Define the vertex shader in GLSL
		string vShaderStr = readShaderSource("shaders/vShader.glsl");
		const char* vShaderSource = vShaderStr.c_str();

		// Define the fragment shader in GLSL
		string fShaderStr = readShaderSource("shaders/fShader.glsl");
		const char* fShaderSource = fShaderStr.c_str();

		// Create unsigned integer IDs for both shaders
		GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Assign the defined vertex shader source code and compile it
		glShaderSource(vShader, 1, &vShaderSource, NULL);
		glCompileShader(vShader);
		checkOpenGLError();
		glGetShaderiv(vShader, GL_COMPILE_STATUS, &vCompiled);
		if (vCompiled != 1) {
			cout << "Vertex Shader Compilation Failed..." << endl;
			printShaderLog(vShader);
		}

		// Assign the defined fragment shader source code and compile it
		glShaderSource(fShader, 1, &fShaderSource, NULL);
		glCompileShader(fShader);
		checkOpenGLError();
		glGetShaderiv(fShader, GL_COMPILE_STATUS, &fCompiled);
		if (fCompiled != 1) {
			cout << "Fragment Shader Compilation Failed..." << endl;
			printShaderLog(fShader);
		}

		// Create an unsigned integer that will hold the ID of the shader program
		GLuint vfProgram = glCreateProgram();

		// Attach both shaders to the shader program ID
		glAttachShader(vfProgram, vShader);
		glAttachShader(vfProgram, fShader);

		// Ensure that the attached shaders are compatible
		glLinkProgram(vfProgram);
		checkOpenGLError();
		glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
		if (linked != 1) {
			cout << "Linking Failed..." << endl;
			printProgramLog(vfProgram);
		}

		return vfProgram;
	}

	// Reads the contents of a .GLSL file to determine the source code of a shader
	string readShaderSource(const char* filePath) {
		// Create a return value that will store the shader source code
		string content;

		// Read the contents of the .GLSL file
		ifstream fileStream(filePath, ios::in);
		string line = "";
		while (!fileStream.eof()) {
			getline(fileStream, line);
			content.append(line + "\n");
		}
		fileStream.close();

		return content;
	}

	// Creates the ID of a texture given its image file path
	GLuint loadtexture(const char* textureImageFilePath) {
		// Create a unsigned integer to hold the ID of your texture
		GLuint textureID;

		// Load the texture by leveraging the SOIL2 library
		textureID = SOIL_load_OGL_texture(textureImageFilePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

		// Ensure that the texture has been loaded correctly
		if (textureID == 0) {
			cout << "Could not find texture file for " << textureImageFilePath << endl;
			return 0;
		}

		// Define Mipmapping
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glGenerateMipmap(GL_TEXTURE_2D);

		// Define Anisotropic Filtering
		if (glewIsSupported("GL_EXT_texture_filter_anisotropic")) {
			GLfloat anisoSetting = 0.0f;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoSetting);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoSetting);
		}

		return textureID;
	}

	// Display the contents of OpenGL's log when GLSL compilation fails
	void printShaderLog(GLuint shader) {
		int len = 0;
		int chWrittn = 0;
		char* log;

		// Retrieve the length of the GLSL compilation log
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

		// Print the log's contents if it is longer than 0 characters
		if (len > 0) {
			log = (char*)malloc(len);
			glGetShaderInfoLog(shader, len, &chWrittn, log);
			cout << "Shader Info Log: " << log << endl;
			free(log);
		}
	}

	// Display the contents of OpenGL's log when GLSL linking fails
	void printProgramLog(int program) {
		int len = 0;
		int chWrittn = 0;
		char* log;

		// Retrieve the length of the GLSL linking log
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		// Print the log's contents if it is longer than 0 characters
		if (len > 0) {
			log = (char*)malloc(len);
			glGetProgramInfoLog(program, len, &chWrittn, log);
			cout << "Program Info Log: " << log << endl;
			free(log);
		}
	}

	// Checks the OpenGL error flag for the occurrence of an OpenGL error
	bool checkOpenGLError(void) {
		// Create a flag that keeps track of OpenGL's error state
		bool errorFound = false;

		// Determine the error state of OpenGL
		int glError = glGetError();

		while (glError != GL_NO_ERROR) {
			cout << "glError: " << glError << endl;
			errorFound = true;
			glError = glGetError();
		}

		return errorFound;
	}
}