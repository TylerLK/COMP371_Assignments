#version 430

// Input Variables
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texture_coordinates;
layout (location = 2) in vec3 normal;

// Output Variables
out vec2 vertex_texture_coordinates;
out vec3 vertex_normal;

// Local Uniform Variables
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform bool show_wireframe;  // NOT USED

void main(void) {
	// Pass your vertex positional data to the fragment shader
	vec4 vertex_position = vec4(position, 1.0);
	
	gl_Position = projection_matrix * view_matrix * model_matrix * vertex_position;

	// Pass your vertex texture coordinates to the fragment shader
	vertex_texture_coordinates = texture_coordinates;

	// Pass your vertex normal data to the fragment shader
	vertex_normal = normal;
}