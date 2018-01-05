#version 330 core

out vec3 nextStepDensity;
in vec2 vsTexCoords;

uniform int N;
uniform sampler2D previousDensitySampler;
uniform float dt;
uniform float kineticViscosity;

/*
   [U]
[L][C][R]
   [D]
*/

void main() {
	vec2 texCoords = vec2(vsTexCoords.x, 1.0f-vsTexCoords.y);

	vec3 previousDensityAndVelocity = texture (previousDensitySampler, texCoords).xyz;
	float prevD = previousDensityAndVelocity.r;
	float squareDim = 1.0 / N;
	float alpha = (squareDim * squareDim) / (kineticViscosity	* dt);
	float beta = 1.0 / (4 + alpha);

	float UDens = texture (previousDensitySampler, texCoords + vec2 (0, -squareDim)).r;
	float DDens = texture (previousDensitySampler, texCoords + vec2 (0, squareDim)).r;
	float LDens = texture (previousDensitySampler, texCoords + vec2 (-squareDim, 0)).r;
	float RDens = texture (previousDensitySampler, texCoords + vec2 (squareDim, 0)).r;

	float newDens = (UDens + DDens + LDens + RDens + alpha * prevD) * beta;

	nextStepDensity = vec3 (newDens, previousDensityAndVelocity.y, previousDensityAndVelocity.z);
}
