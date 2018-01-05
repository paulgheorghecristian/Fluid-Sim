#version 330 core

out vec3 nextStepDensity;
in vec2 vsTexCoords;

uniform int N;
uniform sampler2D previousDensitySampler;
uniform float dt;

void main() {
	vec2 texCoords = vec2(vsTexCoords.x, vsTexCoords.y);

	vec3 previousDensityAndVelocity = texture (previousDensitySampler, texCoords).xyz;
	vec2 velocity = previousDensityAndVelocity.yz;

	vec2 lastPosition = texCoords - vec2(1,1);

	float newDens = texture (previousDensitySampler, lastPosition).r;

	nextStepDensity = vec3 (newDens, previousDensityAndVelocity.y, previousDensityAndVelocity.z);
}
