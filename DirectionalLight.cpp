#include "DirectionalLight.h"
#include "vector3.h"
#include "ext.h"

DirectionalLight::DirectionalLight(float3 position, float3 direction, float3 ambient, float3 diffuse, float3 specular, float shininess, Texture* texture)
									: Light(position, ambient, diffuse, specular, shininess, texture), _direction(direction)
{
}

float3 DirectionalLight::calculate(Fragment& frag, VertexProcessor& vp)
{
    float4 fPos = vp.obj2world * -frag.position;
    float3 v = { fPos.x, fPos.y, fPos.z };

    float4 norm = vp.objrot * frag.normal;
    float3 n = { norm.x, norm.y, norm.z };
    n.normalize();
    float3 l = _direction;
    l.normalize();
    v.normalize();

    //float3 r = float3::reflect(l, n);

    float diff = std::max(l.ndotProduct(n), 0.0f);
    float3 halfwayDir = (l + vp.viewDir).normalize();
    float spec = pow(std::max(halfwayDir.ndotProduct(n), 0.0f), _shininess);
    // combine results
    float3 color = getTexture() != nullptr ? getTexture()->getPixel(frag.uv.x, frag.uv.y) : float3(255, 255, 255);
    color /= 255;
    float3 ambient = _ambient * color;
    float3 diffuse = _diffuse * diff * color;
    float3 specular = _specular * spec * color;

    ambient += diffuse;
    ambient += specular;

    ambient.x = clamp(ambient.x, 0.0f, 255.0f);
    ambient.y = clamp(ambient.y, 0.0f, 255.0f);
    ambient.z = clamp(ambient.z, 0.0f, 255.0f);

    return ambient;
}
