#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL2.h>

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include "Utils.h"
#include "Driver.h"

using namespace std;

// Local Variables
constexpr int NUM_VAO = 1;                                    // Number of Vertex Array Objects
constexpr int NUM_VBO = 1;                                    // Number of Vertex Buffer Objects
constexpr int WINDOW_WIDTH = 600;                             // Window width
constexpr int WINDOW_HEIGHT = 600;                            // Window height
constexpr const char* WINDOW_TITLE = "COMP371 Assignment#3";  // Window title
constexpr float ROTATION_ANGLE = 45.0f;                       // Rotation of the model (In degrees)
constexpr float FOVY = 45.0f;                                 // Field of view in the y direction
constexpr float Z_NEAR = 0.1f;                                // Near-clipping plane
constexpr float Z_FAR = 1000.0f;                              // Far-clipping plane

GLuint renderingProgram; // Holds the Shader Program ID
GLuint vao[NUM_VAO];     // Holds the ID of the Vertex Array Object(s)
GLuint vbo[NUM_VBO];     // Holds the ID of the Vertex Buffer Object(s)

float cameraLocX, cameraLocY, cameraLocZ;    // Initial location data for your camera
float pyramidLocX, pyramidLocY, pyramidLocZ; // Initial location data for your pyramid

GLuint modelLoc;       // Holds the ID of the model matrix GLSL uniform variable
GLuint viewLoc;        // Holds the ID of the view matrix GLSL uniform variable
GLuint projectionLoc;  // Holds the ID of the projection matrix GLSL uniform variable
int width;             // The width of the window (In Pixels)
int height;            // The height of the window (In Pixels)
float aspectRatio;     // The aspect ratio of the window (width / height)

const glm::mat4 iMat(1.0f);                          // 4x4 Identity matrix
glm::mat4 modelMatrix, viewMatrix, projectionMatrix; // 4x4 model, view, and perspective matrices

Driver modelDriver;

// Redering Function Prototypes
void setupVertices(void);
void init(GLFWwindow* window);
void display(GLFWwindow* window, double currentTime);
void window_resize_callback(GLFWwindow* window, int newWidth, int newHeight);

int main(void) {
	// Initialize the GLFW Library
	if (!glfwInit()) {
		cout << "GLFW initialization failed..." << endl;
		return EXIT_FAILURE;
	}

	// Create a window & context to hold the content created by the current program
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
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

	// Ensure the rendered scene is displayed properly, even when the window is resized
	glfwSetWindowSizeCallback(window, window_resize_callback);

	// Initialize the attributes of your OpenGL context
	init(window);

	// Create the main program loop.
	while (!glfwWindowShouldClose(window)) {
		modelDriver.processInput(window); // Process user input for the current frame

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
	// Define the vertices for the model
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
	glGenVertexArrays(NUM_VAO, vao);
	glBindVertexArray(vao[0]);

	// Define and bind a VBO for the current OpenGL program
	glGenBuffers(NUM_VBO, vbo);
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

	// Initialize the object containing all of the Pyramid object's current state variable
	modelDriver = Driver(glm::vec3(pyramidLocX, pyramidLocY, pyramidLocZ));

	// Enable built-in Z-Buffering Algorithm for hidden surface removal
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Set up all vertices, VAOs, & VBOs
	setupVertices();

	// Build Projection Matrix (This is done in "init()" once, for performance purposes)
	// Retrieve the width and height information of the window
	glfwGetFramebufferSize(window, &width, &height);

	// Calculate the aspect ratio of the window
	aspectRatio = (float)width / (float)height;


	projectionMatrix = glm::perspective(glm::radians(FOVY), aspectRatio, Z_NEAR, Z_FAR);
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
	modelMatrix = modelDriver.getModelMatrix();

	// Build the View Matrix
	// Create the eye (i.e. the oiion of  hecamera in the world)
	glm::vec3 eye(cameraLocX, cameraLocY, cameraLocZ);


	// Create the at (i.e, the point in the world space that the camera is looking at)
	glm::vec3 at(0.0f, 0.0f, 0.0f); // The camera is looking at the origin of the world coordinate system

	// Create the up (i.e., the vector that defines the up direction for the camera)
	glm::vec3 up(0.0f, 1.0f, 0.0f);

	viewMatrix = glm::lookAt(eye, at, up);

	// Send the model, view, and perspective matrices to their GLSL uniform variable counterparts
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Re-bind the VAO to ensure the correct vertex data is being drawn
	glBindVertexArray(vao[0]);

	// Uncomment this line to see the wireframe of the model
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Define the front face of your model's primitives as Counter-Clockwise
	glFrontFace(GL_CCW);

	// Initiate the OpenGL pipelining process
	// GL_TRIANGLES: Type of primitive used
	// 0: Which vertex to start with
	// 18: The number of vertices to render
	glDrawArrays(GL_TRIANGLES, 0, 18);
}

void window_resize_callback(GLFWwindow* window, int newWidth, int newHeight) {
	// The new width and height of the window are provided by the callback
	aspectRatio = (float)newWidth / (float)newHeight;

	// Set the screen regio associated with the framebuffer 
	glViewport(0, 0, newWidth, newHeight);

	// Re-calculate the Projection Matrix
	projectionMatrix = glm::perspective(glm::radians(FOVY), aspectRatio, Z_NEAR, Z_FAR);
}