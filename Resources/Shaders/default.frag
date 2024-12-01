#version 460


layout (location = 3) uniform sampler2D textureArray;


layout (location = 0) in vec2 UV;
layout (location = 1) in float lightIntensity;

layout (location = 0) out vec4 fragColor;


void main() {
    fragColor = vec4(1, 1, 1, 1) * lightIntensity; // texture(textureArray, UV) * lightIntensity;
    fragColor[3] = 1.0f;
}