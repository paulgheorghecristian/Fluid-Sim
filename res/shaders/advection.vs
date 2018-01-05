#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoords;

uniform mat4 projection_matrix;
uniform int N;

out vec2 vsTexCoords;

void main() {
	vsTexCoords = inTexCoords;

	gl_Position = projection_matrix * vec4 (inPosition.xy, -10.0, 1.0);
}
