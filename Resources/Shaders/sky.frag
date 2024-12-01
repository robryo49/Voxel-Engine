#version 460


layout (location = 0) in vec3 vertexPosition;

out vec4 fragColor;


struct skyColor{
    float v;
    vec3 color;
};


skyColor SkyGradient[] = skyColor[](
    skyColor(0.0, vec3(0.8, 0.95, 1.0)),
    skyColor(0.4, vec3(0.7, 0.9, 1.0)),
    skyColor(0.5, vec3(0.3, 0.8, 1.0)),
    skyColor(0.7, vec3(0.0, 0.7, 1.0)),
    skyColor(1.0, vec3(0.0, 0.5, 1.0))
);


int numColors = 5;
float pi = 3.14159;


vec2 getCorrectYawPitch ( vec3 v ) {
    float x = v.x;
    float y = v.y;
    float z = v.z;

    vec2 vec = v.xz;

    float r = sqrt(pow(x, 2) + pow(z, 2));

    float yaw = atan(abs(z) / abs(x));
    //vec2 sqVec = vec2(min(1, tan(pi / 2 - yaw)), min(1, tan(yaw)));
    yaw = (pi / 4) * (min(1, tan(yaw)) + 1 - min(1, tan(pi / 2 - yaw)));
    x = cos(yaw) * r;
    z = sin(yaw) * r;

    float pitch = atan(y / abs(r));

    return vec2(yaw, pitch);
}


vec3 getColor(float pitch) {

    float prog = pitch / pi + 0.5;

    int colorNum;

    for (colorNum; colorNum < numColors - 1; colorNum++) {
        if (SkyGradient[colorNum].v <= prog && prog <= SkyGradient[colorNum + 1].v) break;
    }

    float stepProg = (prog - SkyGradient[colorNum].v) / (SkyGradient[colorNum + 1].v - SkyGradient[colorNum].v);
    return mix(SkyGradient[colorNum].color, SkyGradient[colorNum + 1].color, stepProg); //SkyGradient[colorNum].color * (1 - stepProg) + SkyGradient[colorNum + 1].color * stepProg;
}


void main() {

    vec2 uv = vec2(gl_FragCoord.xy) / vec2(1080, 720);
    vec2 orientation = getCorrectYawPitch(vertexPosition);

    float yaw = orientation.x;
    float pitch = orientation.y;

    vec3 color = getColor(pitch);

    fragColor = vec4(color, 1);
}