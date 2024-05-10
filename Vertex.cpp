#include "Vertex.h"

Vertex::Vertex(float3 Position, float3 Normal) : position(Position), normal(Normal)
{
}

Vertex::Vertex(float3 Position, float3 Normal, float3 UV) : position(Position), normal(Normal), uv(UV)
{
}
