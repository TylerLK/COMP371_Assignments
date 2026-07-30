#version 430

in vec4 vertex_colour;

out vec4 fragment_colour;

void main(void) {
	fragment_colour = vertex_colour;
}