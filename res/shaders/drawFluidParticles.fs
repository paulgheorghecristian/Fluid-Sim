#version 330 core

in vec2 vsTexCoords;
out vec4 outColor;

uniform int N;
uniform sampler2D densityAndVelocitySampler;

void main() {
	vec3 data = texture (densityAndVelocitySampler, vec2(vsTexCoords.x, vsTexCoords.y)).xyz;

	outColor = vec4 (data.r, data.r, data.r, 1.0);
}
