#pragma once
#include "Type.h"
namespace mm {
	/// <summary>
	/// ��ȡ�ص����ֵĶ��㣬�����ཻ�Ķ�����ڲ��Ķ���
	/// </summary>
	/// <param name="mesh0"></param>
	/// <param name="mesh1"></param>
	/// <param name="vertices"></param>
	/// <returns></returns>
	int Intersection(const Surface_mesh& mesh0, const Surface_mesh& mesh1, Surface_mesh& outMesh);
}
