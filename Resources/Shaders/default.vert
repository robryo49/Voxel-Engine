#version 460


layout (location = 0) uniform mat4 mCamera;


layout (location = 0) in int vertexData;


layout (location = 0) out vec2 UV;
layout (location = 1) out float lightIntensity;


float ambientLight = 0.3;
float sunLightIntensity = 1.0f;


vec3 faceNormals[6] = vec3[6](
    vec3(0, 1, 0),
    vec3(0, -1, 0),
    vec3(-1, 0, 0),
    vec3(1, 0, 0),
    vec3(0, 0, -1),
    vec3(0, 0, 1)
);
vec3 faceNormal;
vec3 sunDir = normalize(vec3(0.5, 1, 0.2));


vec3 hashVec3(int value) {
    // Simple hash function to generate RGB values
    float r = fract(sin(float(value) * 0.1 + 3.14) * 43758.7857);
    float g = fract(sin(float(value) * 0.2 + 3.14) * 37852.2542);
    float b = fract(sin(float(value) * 0.3 + 3.14) * 78578.4254);

    // Scale to 0-1 range and convert to 0-255 range
    return vec3(r, g, b);
};


void main()
{
    uint vertexID = (vertexData >> 29) & 3;

    uint faceID = (vertexData >> 26) & 7;

    uint voxelID = (vertexData >> 18) & 255;

    uint z = (vertexData >> 12) & 63;

    uint y = (vertexData >> 6) & 63;

    uint x = (vertexData) & 63;

    vec3 inPosition = vec3(x, y, z);

    faceNormal = faceNormals[faceID];
    float sunLight = (1 + dot(faceNormal, -sunDir)) / 2;
    sunLight = sunLight * (1-ambientLight) + ambientLight;

    UV = vec2(vertexID % 2, vertexID / 2);

    lightIntensity = sunLight * sunLightIntensity;

    gl_Position = mCamera * vec4(inPosition, 1.0);
}