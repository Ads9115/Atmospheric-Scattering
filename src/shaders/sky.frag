#version 330 core

in vec2 uv;

out vec4 FragColor;

uniform mat4 invProjection;
uniform mat4 invView;
uniform vec3 cameraPos;
uniform vec3 sunDirection;
uniform float sunIntensity;
uniform float groundRadius;
uniform float atmosphereRadius;
uniform vec3 betaR;
uniform float Hr;
uniform int viewSamples;
uniform int lightSamples;
uniform float betaM;
uniform float Hm;
uniform float mieG;
uniform float exposure;


const float PI = 3.14159265359;

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
    
    if (!hitAtmosphere)
    {
      FragColor = vec4(0.0, 0.0, 0.0, 1.0);
      return;
    }

    float tGround0;
    float tGround1;

    bool hitGround = RaySphereIntersection(cameraPos, rayDir, groundRadius, tGround0, tGround1);

    if (hitGround && tGround0 > 0.0)
  {
      FragColor = vec4(0.03, 0.025, 0.02, 1.0);
      return;
  }

    float tStart = 0.0;
    float tEnd = tAtmosphere1;

    

    float segmentLength = (tEnd - tStart) / float(viewSamples);
    vec3 accumulatedR = vec3(0.0);
    vec3 accumulatedM = vec3(0.0);
    float opticalDepthR = 0.0;
    float opticalDepthM = 0.0;

    for(int i = 0; i < viewSamples; i++){

        float t = tStart + (float(i) + 0.5) * segmentLength;
        vec3 samplePos = cameraPos + rayDir * t;

        float height = length(samplePos) - groundRadius;
        float sampleDepthR = exp(-height / Hr) * segmentLength;
        float sampleDepthM = exp(-height / Hm) * segmentLength;

        opticalDepthR += sampleDepthR;
        opticalDepthM += sampleDepthM;

        float tLightGround0, tLightGround1;
        bool hitLightGround = RaySphereIntersection(samplePos, sunDirection, groundRadius, tLightGround0, tLightGround1);
        if (hitLightGround && tLightGround0 > 0.0) {
            continue;
        }

        float tLight0, tLight1;
        bool hitLightAtmosphere = RaySphereIntersection(samplePos, sunDirection, atmosphereRadius, tLight0, tLight1);

        if(hitLightAtmosphere) {

            float lightSegmentLength = tLight1 / float(lightSamples);
            float lightOpticalDepthR = 0.0;
            float lightOpticalDepthM = 0.0;

            for (int j = 0; j < lightSamples; ++j) {
                float tLight = (float(j) + 0.5) * lightSegmentLength;
                vec3 lightSamplePos = samplePos + sunDirection * tLight;

                float lightHeight = length(lightSamplePos) - groundRadius;
                lightOpticalDepthR += exp(-lightHeight / Hr) * lightSegmentLength;
                lightOpticalDepthM += exp(-lightHeight / Hm) * lightSegmentLength;
            }

            vec3 transmittance = exp(-(
                betaR * (opticalDepthR + lightOpticalDepthR) +
                vec3(betaM * 1.1) * (opticalDepthM + lightOpticalDepthM)
            ));

            accumulatedR += sampleDepthR * transmittance;
            accumulatedM += sampleDepthM * transmittance;
        }
    }

    float mu = dot(rayDir, sunDirection);
    float phaseR = (3.0 / (16.0 * PI)) * (1.0 + mu * mu);
    float phaseM = (3.0 / (8.0 * PI)) *
                 ((1.0 - mieG * mieG) * (1.0 + mu * mu)) /
                 ((2.0 + mieG * mieG) * pow(1.0 + mieG * mieG - 2.0 * mieG * mu, 1.5));

    vec3 color = sunIntensity * (
      betaR * phaseR * accumulatedR +
      vec3(betaM) * phaseM * accumulatedM
    );


    color = 1.0 - exp(-color * exposure);
    color = pow(color, vec3(1.0 / 2.2));
    color = clamp(color, 0.0, 1.0);
    FragColor = vec4(color, 1.0);
    




}


