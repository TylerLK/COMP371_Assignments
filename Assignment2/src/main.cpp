#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Utils.h"
#include "Shader.h"

using namespace std;

// Local Variables
constexpr int NUMVAOS = 1; // Number of Vertex Array Objects
constexpr int NUMVBOS = 1; // Number of Vertex Buffer Objects

GLuint renderingProgram; // Holds the Shader Program ID
GLuint vao[NUMVAOS];     // Holds the ID of the Vertex Array Object(s)
GLuint vbo[NUMVBOS];     // Holds the ID of the Vertex Buffer Object(s)

float cameraLocX, cameraLocY, cameraLocZ;    // Initial location data for your camera
float pyramidLocX, pyramidLocY, pyramidLocZ; // Initial location data for your pyramid

GLuint modelLoc;       // Holds the ID of the model matrix GLSL uniform variable
GLuint viewLoc;        // Holds the ID of the view matrix GLSL uniform variable
GLuint projectionLoc;  // Holds the ID of the projection matrix GLSL uniform variable
int width;             // The width of the window (In Pixels)
int height;            // The height of the window (In Pixels)
float aspectRatio;     // The aspect ratio of the window (width / height)

glm::mat4 modelMatrix, viewMatrix, projectionMatrix; // 4x4 model, view, and perspective matrices

// Redering Function Prototypes
void setupVertices(void);
void init(GLFWwindow* window);
void display(GLFWwindow* window, double currentTime);

int main(void) {
	// Initialize the GLFW Library
	if (!glfwInit()) {
		cout << "GLFW initialization failed..." << endl;
		return EXIT_FAILURE;
	}

	// Create a window & context to hold the content created by the current program
	GLFWwindow* window = glfwCreateWindow(600, 600, "COMP371 Assignment#2", NULL, NULL);
	if (!window) {
		cout << "Window creation failed..." << endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Ensure that the context displayed in the window is the current context
	glfwMakeContextCurrent(window);

	// Enable V-Sync to lock the GPU's frame rate to the monitor refresh rate
	glfwSwapInterval(1);

	// Initialize the GLEW Library
	if (glewInit() != GLEW_OK) {
		cout << "GLEW initialization failed..." << endl;
		return EXIT_FAILURE;
	}

	// Initialize the attributes of your OpenGL context
	init(window);
	
	// TODO: Integrate the callback functions here

	// Create the main program loop.
	while (!glfwWindowShouldClose(window)) {
		// ender the desired scene in the OpenGL context
		display(window, glfwGetTime());

		// Swap the front and back buffers to display the rendered image
		glfwSwapBuffers(window);

		// Poll for and process events (keyboard, mouse, etc.)
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}

// Creates and initializes the vertices, VAO(s), and VBO(s) for the OpenGL program
void setupVertices(void) {
	// Define the vertices for the Pyramid
	// 6 Triangles -> 18 Vertices -> 54 indices
	float vertexPositions[54]{
		-1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Front Face
		1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // Right Face
		1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // Back Face
		-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Left Face
		-1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, // Bottom Face (Left + Front)
		1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f // Bottom Face (Front + Right)
	};

	// Define and bind a VAO for the current OpenGL program
	glGenVertexArrays(NUMVAOS, vao);
	glBindVertexArray(vao[0]);

	// Define and bind a VBO for the current OpenGL program
	glGenBuffers(NUMVBOS, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

	// Associate the VBO to the Vertex Attribute Pointer for the current OpenGL program
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

// Initialize the attributes of your OpenGL context
void init(GLFWwindow* window) {
	// Create a shader program
	renderingProgram = Utils::createShaderProgram();

	// Initialize the position for both your camera and pyramid
	cameraLocX = 0.0f;
	cameraLocY = 0.0f;
	cameraLocZ = 5.0f;

	pyramidLocX = 0.0f;
	pyramidLocY = 0.0f;
	pyramidLocZ = 0.0f;

	// Set up all vertices, VAOs, & VBOs
	setupVertices();
}

// Renders the desired scene in the OpenGL context
// Passing the current time as a parameter ensures that the scene is animated at the
// same rate, regardless of the computer's speed.
void display(GLFWwindow* window, double currentTime) {
	// Clear the background of the window & ensure that depth comparisons are not affected by old data
	glClearColor(0.0, 0.0, 0.0, 1.0); // Clear colour is Black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Load the shader program into the current context
	glUseProgram(renderingProgram);

	// Retrieve the GLSL uniform variable pointers for the model, view, and perspective matrices
	modelLoc = glGetUniformLocation(renderingProgram, "model_matrix");
	viewLoc = glGetUniformLocation(renderingProgram, "view_matrix");
	projectionLoc = glGetUniformLocation(renderingProgram, "projection_matrix");

	// Build the Model Matrix
	modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(pyramidLocX, pyramidLocY, pyramidLocZ));

	// Build the View Matrix
	// Create the eye (i.e. the oiion of  hecamera in the world)
	glm::vec3 eye(cameraLocX, cameraLocY, cameraLocZ);


	// Create the at (i.e, the point in the world space that the camera is looking at)
	glm::vec3 at(0.0f, 0.0f, 0.0f); // The camera is looking at the origin of the world coordinate system

	// Create the up (i.e., the vector that defines the up direction for the camera)
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	viewMatrix = glm::lookAt(eye, at, up);

	// Build the Perspective Matrix
	// Retrieve the width and height information of the window
	glfwGetFramebufferSize(window, &width, &height);

	// Define the Field of View in the y-direction (In Radians)
	float fovy = 45.0f; // 45 degrees

	// Calculate the aspect ratio of the window
	aspectRatio = (float)width / (float)height;

	// Define the near and far clipping plane distances
	float near = 0.1f; // Near-clipping plane
	float far = 100.0f; // Far-clipping plane

	projectionMatrix = glm::perspective(glm::radians(fovy), aspectRatio, near, far);

	// Send the model, view, and perspective matrices to their GLSL uniform variable counterparts
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Re-bind the VAO to ensure the correct vertex data is being drawn
	glBindVertexArray(vao[0]);

	// Enable built-in Z-Buffering Algorithm for hidden surface removal
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Initiate the OpenGL pipelining process
	// GL_TRIANGLES: Type of primitive used
	// 0: Which vertex to start with
	// 18: The number of vertices to render
	glDrawArrays(GL_TRIANGLES, 0, 18);
}