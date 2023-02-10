#pragma once
#include "Type.h"
namespace mm {
	int Merge(std::vector<Surface_mesh>& meshs, Surface_mesh& outMesh);
	int Merge(const Surface_mesh& mesh0, const Surface_mesh& mesh1, const std::vector<Vertex_descriptor>& vd0, const std::vector<Vertex_descriptor>& vd1, Surface_mesh& outMesh);
}
