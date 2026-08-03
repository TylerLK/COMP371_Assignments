#version 430

layout (location = 0) in vec3 position;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec4 vertex_colour;

void main(void) {
	vec4 vertex_position = vec4(position, 1.0);
	
	gl_Position = projection_matrix * view_matrix * model_matrix * vertex_position;

	vertex_colour = (vertex_position * 0.5) + vec4(0.5, 0.5, 0.5, 0.5);
}