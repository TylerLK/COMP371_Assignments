#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL2.h>
#include <tiny_obj_loader.h>

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

#include "Utils.h"
#include "Driver.h"

using namespace std;

// Local Variables
constexpr int NUM_VAO = 1;                                    // Number of Vertex Array Objects
constexpr int NUM_VBO = 3;                                    // Number of Vertex Buffer Objects
constexpr int WINDOW_WIDTH = 600;                             // Window width
constexpr int WINDOW_HEIGHT = 600;                            // Window height
constexpr const char* WINDOW_TITLE = "COMP371 Assignment #3";  // Window title
constexpr float ROTATION_ANGLE = 45.0f;                       // Rotation of the model (In degrees)
constexpr float FOVY = 45.0f;                                 // Field of view in the y direction
constexpr float Z_NEAR = 0.1f;                                // Near-clipping plane
constexpr float Z_FAR = 1000.0f;                              // Far-clipping plane

GLuint renderingProgram; // Holds the Shader Program ID
GLuint vao[NUM_VAO];     // Holds the ID of the Vertex Array Object(s)
GLuint vbo[NUM_VBO];     // Holds the ID of the Vertex Buffer Object(s)

float cameraLocX, cameraLocY, cameraLocZ;    // Initial location data for your camera
float modelLocX, modelLocY, modelLocZ;       // Initial location data for your model

GLuint modelLoc;       // Holds the ID of the model matrix GLSL uniform variable
GLuint viewLoc;        // Holds the ID of the view matrix GLSL uniform variable
GLuint projectionLoc;  // Holds the ID of the projection matrix GLSL uniform variable
int width;             // The width of the window (In Pixels)
int height;            // The height of the window (In Pixels)
float aspectRatio;     // The aspect ratio of the window (width / height)

const glm::mat4 iMat(1.0f);                          // 4x4 Identity matrix
glm::mat4 modelMatrix, viewMatrix, projectionMatrix; // 4x4 model, view, and perspective matrices

Driver modelDriver;             // Contains the current state of the model's transformation data
vector<float> modelVertexData;  // Holds the vertex position data for the imported model
vector<float> modelTextureData; // Holds the vertex texture data for the imported model
vector<float> modelNormalData;  // Holds the vertex normal data for the imported model
GLuint chairTexture;            // Holds the ID of the model's texture

bool showWireframe = false; // A flag to keep track of whether the raw wireframe should be visible or not
GLuint showWireframeLoc;    // Holds the ID of the wireframe visibility flag GLSL uniform variable

// Redering Function Prototypes
void loadModel(const string& objFilePath);
void setupVertices(void);
void init(GLFWwindow* window);
void display(GLFWwindow* window, double currentTime);
void window_resize_callback(GLFWwindow* window, int newWidth, int newHeight);
void show_wireframe_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

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

	// Ensure that the drawing mode is toggled when the 'X' key is pressed
	glfwSetKeyCallback(window, show_wireframe_callback);

	// Initialize the attributes of your OpenGL context
	init(window);

	// Create the main program loop.
	while (!glfwWindowShouldClose(window)) {
		// Process user input for the current frame
		modelDriver.processInput(window);

		// Render the desired scene in the OpenGL context
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

// Loads an external DDC tool model given a .obj file's path
void loadModel(const string& objFilePath) {
	// Define the data structures for holding raw .obj file data
	tinyobj::attrib_t attrib;
	vector<tinyobj::shape_t> shapes;
	vector<tinyobj::material_t> materials;
	string warning, error;

	// Ensure the .obj file data is loaded correctly into the data defined structures
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error, objFilePath.c_str())) {
		cerr << "Failed to load: " << error << endl;
		return;
	}

	// Ensure the float vectors are empty before transferring the vertex, texture, and normal data
	modelVertexData.clear();
	modelTextureData.clear();
	modelNormalData.clear();

	// Iterate through all the shape_t objects in "shapes"
	for (size_t shape = 0; shape < shapes.size(); shape++) {
		// Determine the number of primitives in the current shape_t object
		size_t num_shape_primitives = shapes[shape].mesh.num_face_vertices.size();

		// Iterate through each primitive in the current shape_t object
		for (size_t primitive = 0; primitive < num_shape_primitives; primitive++) {
			// Determine the number of vertices in the current primitive (Should be 3)
			size_t num_primitive_vertices = shapes[shape].mesh.num_face_vertices[primitive];

			// Iterate through each vertex to construct the vertex, texture, and normal data
			for (size_t vertex = 0; vertex < num_primitive_vertices; vertex++) {
				// Determine the index of the current vertex
				tinyobj::index_t index = shapes[shape].mesh.indices[primitive * num_primitive_vertices + vertex];

				// Transfer the vertex position data
				modelVertexData.push_back(attrib.vertices[3 * size_t(index.vertex_index) + 0]); // x Coordinate
				modelVertexData.push_back(attrib.vertices[3 * size_t(index.vertex_index) + 1]); // y Coordinate
				modelVertexData.push_back(attrib.vertices[3 * size_t(index.vertex_index) + 2]); // z Coordinate

				// Transfer the vertex texture data, if it exists
				if (index.texcoord_index >= 0) {
					modelTextureData.push_back(attrib.texcoords[2 * size_t(index.texcoord_index) + 0]); // u Coordinate
					modelTextureData.push_back(attrib.texcoords[2 * size_t(index.texcoord_index) + 1]); // v Coordinate
				}

				// Transfer the vertex normal data, if it exists
				if (index.normal_index >= 0) {
					modelNormalData.push_back(attrib.normals[3 * size_t(index.normal_index) + 0]); // x Direction
					modelNormalData.push_back(attrib.normals[3 * size_t(index.normal_index) + 1]); // y Direction
					modelNormalData.push_back(attrib.normals[3 * size_t(index.normal_index) + 2]); // z Direction
				}

			}
		}
	}
}

// Creates and initializes the VAO(s) and VBO(s) for the OpenGL program
void setupVertices(void) {
	// Define and bind a VAO for the current OpenGL program
	glGenVertexArrays(NUM_VAO, vao);
	glBindVertexArray(vao[0]);

	// Define the VBO(s) for the current OpenGL program
	glGenBuffers(NUM_VBO, vbo);

	// Bind vbo[0] to Vertex Position Data
	if (!modelVertexData.empty()) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, modelVertexData.size() * sizeof(float), modelVertexData.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}

	// Bind vbo[1] to Vertex Texture Data
	if (!modelTextureData.empty()) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, modelTextureData.size() * sizeof(float), modelTextureData.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}

	// Bind vbo[2] to Vertex Normal Data
	if (!modelNormalData.empty()) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, modelNormalData.size() * sizeof(float), modelNormalData.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);
	}
}

// Initialize the attributes of your OpenGL context
void init(GLFWwindow* window) {
	// Create a shader program
	renderingProgram = Utils::createShaderProgram();

	// Initialize the position for both your camera and pyramid
	cameraLocX = 0.0f;
	cameraLocY = 10.0f;
	cameraLocZ = 30.0f;

	modelLocX = 0.0f;
	modelLocY = 0.0f;
	modelLocZ = 0.0f;

	// Initialize the object containing all of the Pyramid object's current state variable
	modelDriver = Driver(glm::vec3(modelLocX, modelLocY, modelLocZ), ROTATION_ANGLE);

	// Enable built-in Z-Buffering Algorithm for hidden surface removal
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Enable face culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	// Load the external DCC model
	loadModel("assets/models/chair.obj");

	// Set up all vertices, VAOs, & VBOs
	setupVertices();

	// Build Projection Matrix (This is done in "init()" once, for performance purposes)
	// Retrieve the width and height information of the window
	glfwGetFramebufferSize(window, &width, &height);

	// Calculate the aspect ratio of the window
	aspectRatio = (float)width / (float)height;

	projectionMatrix = glm::perspective(glm::radians(FOVY), aspectRatio, Z_NEAR, Z_FAR);

	// Load the texture of the model
	chairTexture = Utils::loadtexture("assets/textures/chairTexture.jpg");
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
	showWireframeLoc = glGetUniformLocation(renderingProgram, "show_wireframe");

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
	glUniform1i(showWireframeLoc, showWireframe);

	// Re-bind the VAO to ensure the correct vertex data is being drawn
	glBindVertexArray(vao[0]);

	if (showWireframe) {
		// Render the wireframe of the model
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		// Render solid polygons for the model
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// Initiate the OpenGL pipelining process
	glDrawArrays(GL_TRIANGLES, 0, (modelVertexData.size() / 3));
}

// Adapts the rendered image to the window when it is resized
void window_resize_callback(GLFWwindow* window, int newWidth, int newHeight) {
	// The new width and height of the window are provided by the callback
	aspectRatio = (float)newWidth / (float)newHeight;

	// Set the screen regio associated with the framebuffer 
	glViewport(0, 0, newWidth, newHeight);

	// Re-calculate the Projection Matrix
	projectionMatrix = glm::perspective(glm::radians(FOVY), aspectRatio, Z_NEAR, Z_FAR);
}

// Toggles the visibility of the wireframe when the 'X' key is pressed
void show_wireframe_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		showWireframe = !showWireframe;
	}
}