#version 330

#ifdef DEBUG
    #pragma optimize(off)
    #pragma debug(on)
#else
    #pragma optimize(on)
    #pragma debug(off)
#endif

// global uniform
uniform vec3        CameraPos;
uniform vec3        LightDir;

// define the colors intensity
uniform float       AmbientIntensity    =   0.5f;
uniform float       DiffuseIntensity    =   0.5f;
uniform float       SpecularIntensity   =   0.5f;

// material data
struct Material
{
    vec4    _Ka;
    vec4    _Kd;
    vec4    _Ks;
};
#define MAX_MATERIAL_COUNT  256
layout (std140, shared) uniform Materials
{
    Material    materials[MAX_MATERIAL_COUNT];
};
#define GET_KA(index)       materials[index]._Ka.xyz
#define GET_KD(index)       materials[index]._Kd.xyz
#define GET_KS(index)       materials[index]._Ks.xyz
#define GET_MAP_KA(index)   materials[index]._Ka.w
#define GET_MAP_KD(index)   materials[index]._Kd.w
#define GET_NS(index)       materials[index]._Ks.w


// input form vs
in VS_OUT
{
    vec3        position;
    vec3        normal;
    flat int    matIndex;
}vs;
#define KA      GET_KA(vs.matIndex)
#define KD      GET_KD(vs.matIndex)
#define KS      GET_KS(vs.matIndex)
#define MapKA   GET_MAP_KA(vs.matIndex)
#define MapKD   GET_MAP_KD(vs.matIndex)
#define NS      GET_NS(vs.matIndex)


// output color
out     vec4    fragColor;

/**
 * Phong light
 */
vec3 phong(const in vec3 normal, float shadowFactor)
{
    vec3 ambient = KA * AmbientIntensity;
    float NdotL = max(dot(normal, LightDir), 0.0f);
    vec3 diffuse = KD * (DiffuseIntensity * NdotL* shadowFactor);
    
    /* compute the specular term if NdotL is  larger than zero */
    vec3 specular = vec3(0.0f);
    if (NdotL > 0.0f) 
    {
#ifndef BLINN
        // normalize the half-vector, and then compute the
        // cosine (dot product) with the normal
        vec3 HV = normalize(CameraPos - vs.position);
        float NdotHV = reflect(dot(normal, HV), 0.0f);
        specular = KS * (pow(NdotHV, NS) * SpecularIntensity);
#else
        vec3 H = normalize(CameraPos - vs.position + LightDir);
        specular = KS * (pow(max(0.0, dot(normal, H)), NS) * SpecularIntensity);
#endif
    }
    
    return ambient + (diffuse + specular) * shadowFactor;
}

void main()
{
    vec3 normal = normalize(vs.normal);
    fragColor = vec4(phong(normal, 1), 1);
}
