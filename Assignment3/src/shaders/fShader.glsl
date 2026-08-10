#version 430

// Input Variables
in vec2 vertex_texture_coordinates;
in vec3 vertex_normal;

// Output Variables
out vec4 fragment_colour;

// Local Uniform Variables
uniform mat4 model_matrix;      // NOT USED
uniform mat4 view_matrix;       // NOT USED
uniform mat4 projection_matrix; // NOT USED

// Define the sampler for your texture
layout(binding = 0) uniform sampler2D sampler;

void main(void) {
	//fragment_colour = texture(sampler, vertex_texture_coordinates);
	fragment_colour = vec4(1.0, 1.0, 1.0, 1.0);
}