#version 330 core

in vec2 uv;

out vec4 FragColor;

uniform mat4 invProjection;
uniform mat4 invView;
uniform vec3 cameraPos;
void main()
{
    vec2 ndc = uv * 2.0 - 1.0;

    vec4 clip = vec4(ndc, 1.0, 1.0);

    vec4 view = invProjection * clip;

    view = vec4(view.xy, -1.0, 0.0);

    vec3 rayDir = normalize((invView * view).xyz);

    FragColor = vec4(rayDir * 0.5 + 0.5, 1.0);
}