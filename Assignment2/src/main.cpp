#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

using namespace std;

int main(void) {
	// Initialize the GLFW Library
	if (!glfwInit()) {
		cout << "GLFW initialization failed!" << endl;
		return EXIT_FAILURE;
	}

	// Ensures that the user's machine is compatible with version 4.3 of OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Create a window & context to hold the content created by the current program.
	GLFWwindow* window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
	if (!window) {
		cout << "Window creation failed!" << endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Ensure that the context displayed in the window is the current context.
	glfwMakeContextCurrent(window);

	// Enable V-Sync to achieve Double Buffering for adequate re-drawing speeds.
	glfwSwapInterval(1);

	// Initialize the GLEW Library
	if (glewInit() != GLEW_OK) {
		cout << "GLEW initialization failed!" << endl;
		return EXIT_FAILURE;
	}

	float vertices[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	while (!glfwWindowShouldClose(window)) {
		//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Work with the vertices here.
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableClientState(GL_VERTEX_ARRAY);

		// Swap the Front & Back Buffers.
		glfwSwapBuffers(window);

		// Poll for events and process them accordingly.
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}