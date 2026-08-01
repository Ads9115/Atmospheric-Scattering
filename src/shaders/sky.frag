#version 330 core

in vec2 uv;

out vec4 FragColor;

uniform mat4 invProjection;
uniform mat4 invView;
uniform vec3 cameraPos;

const float groundRadius = 6371.0;
const float atmosphereRadius = 6471.0;

bool RaySphereIntersection(vec3 origin, vec3 dir, float radius, out float t0, out float t1){

    float b = 2.0 * dot(origin, dir);
    float c = dot(origin, origin) - radius * radius;

    float discriminant = b * b - 4.0 * c;

    if(discriminant < 0.0){
        return false;
    }

    float sqrtD = sqrt(discriminant);

    t0 = (-b - sqrtD) * 0.5;
    t1 = (-b + sqrtD) * 0.5;
    
    return true;

}


void main()
{
    vec2 ndc = uv * 2.0 - 1.0;
    vec4 clip = vec4(ndc, 1.0, 1.0);
    vec4 view = invProjection * clip;
    view = vec4(view.xy, -1.0, 0.0);
    vec3 rayDir = normalize((invView * view).xyz);
    
    float tAtmosphere0;
    float tAtmosphere1;

    bool hitAtmosphere = RaySphereIntersection(cameraPos, rayDir, atmosphereRadius, tAtmosphere0, tAtmosphere1);

    float tGround0;
    float tGround1;

    bool hitGround = RaySphereIntersection(cameraPos, rayDir, groundRadius, tGround0, tGround1);

    if (hitGround && tGround0 > 0.0)
    {
      FragColor = vec4(0.05, 0.04, 0.03, 1.0); // ground/dark
      return;
    }

    if (hitAtmosphere)
    {
      FragColor = vec4(0.2, 0.5, 1.0, 1.0); // sky
      return;
    }

    FragColor = vec4(0.0, 0.0, 0.0, 1.0);;




}