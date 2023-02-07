#pragma once
#include "Type.h"
namespace mm {
	int eatEdge(const Surface_mesh& mesh0, const Surface_mesh& mesh1, Surface_mesh& outMesh);
	int eatEdgeVertices(const Surface_mesh& mesh0, const Surface_mesh& mesh1, Point_set& outPoints);
}
