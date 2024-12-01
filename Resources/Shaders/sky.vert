#version 460


layout (location = 0) uniform mat4 mCamera;


layout (location = 0) in ivec3 inPosition;


layout (location = 0) out vec3 vertexPosition;


void main()
{   
    vertexPosition = inPosition;

    vec4 pos = mCamera * vec4(inPosition, 1.0);
    gl_Position = vec4(pos.xy, pos.w, pos.w);
}