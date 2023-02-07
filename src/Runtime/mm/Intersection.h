#pragma once
#include "Type.h"
namespace mm {
	/// <summary>
	/// 获取重叠部分的顶点，包括相交的顶点和内部的顶点
	/// </summary>
	/// <param name="mesh0"></param>
	/// <param name="mesh1"></param>
	/// <param name="vertices"></param>
	/// <returns></returns>
	int Intersection(const Surface_mesh& mesh0, const Surface_mesh& mesh1, Surface_mesh& outMesh);
}
