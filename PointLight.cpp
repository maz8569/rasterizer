#include "PointLight.h"
#include "ext.h"

PointLight::PointLight(float3 position, float3 ambient, float3 diffuse, float3 specular, float shininess, Texture* texture)
	: Light(position, ambient, diffuse, specular, shininess, texture)
{
}

float3 PointLight::calculate(Fragment& frag, VertexProcessor& vp)
{
    float4 fPos = vp.obj2world * -frag.position;
    float3 v = { fPos.x, fPos.y, fPos.z };

    float4 norm = vp.objrot * frag.normal;
    float3 n = { norm.x, norm.y, norm.z };
    n.normalize();
    float3 l = _position - v;
    l.normalize();
    v.normalize();

    float diff = std::max(l.dotProduct(n), 0.0f);
    float3 halfwayDir = (l + vp.viewDir).normalize();
    float spec = pow(std::max(halfwayDir.dotProduct(n), 0.0f), _shininess);
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
