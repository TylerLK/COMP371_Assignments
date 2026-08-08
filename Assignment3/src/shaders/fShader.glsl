#version 430

// Input Variables
in vec4 vertex_colour;

// Output Variables
out vec4 fragment_colour;

// Local Uniform Variables
uniform mat4 model_matrix;      // NOT USED
uniform mat4 view_matrix;       // NOT USED
uniform mat4 projection_matrix; // NOT USED

void main(void) {
	fragment_colour = vertex_colour;
}