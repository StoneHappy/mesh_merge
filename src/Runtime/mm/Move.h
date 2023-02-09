#pragma once
#include "Type.h"
#include <array>
namespace mm
{
	int GetIntersectionBorderPoints(const Surface_mesh& mesh0, const Surface_mesh& mesh1, std::vector<Vertex_descriptor>& vd0, std::vector<Vertex_descriptor>& vd1);

	int MovePoint2Middle(Surface_mesh& mesh0, Surface_mesh& mesh1, const std::vector<Vertex_descriptor>& vd0, const std::vector<Vertex_descriptor>& vd1);
}
