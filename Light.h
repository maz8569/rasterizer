#pragma once
#include "vector3.h"
#include "Vertex.h"
#include "VertexProcessor.h"
#include "Texture.h"

class Light
{
protected:
	float3 _position;
	float3 _ambient;
	float3 _diffuse;
	float3 _specular;
	float _shininess;

	Texture* _texture;


public:

	Light(float3 position, float3 ambient, float3 diffuse, float3 specular, float shininess, Texture* texture = nullptr) : 
				 _position(position), _ambient(ambient), _diffuse(diffuse), _specular(specular), _shininess(shininess), _texture(texture)
	{};

	virtual float3 calculate(Fragment& frag, VertexProcessor& vp) {
		return { 0, 0, 0 };
	}

	Texture* getTexture() const {
		return _texture;
	}

};

