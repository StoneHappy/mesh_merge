#include "Move.h"

namespace mm
{
	int GetIntersectionBorderPoints(const Surface_mesh& mesh0, const Surface_mesh& mesh1, std::vector<Vertex_descriptor>& vd0, std::vector<Vertex_descriptor>& vd1)
	{
		Kernel::Iso_cuboid_3 bbox1 = CGAL::bounding_box(mesh1.points().begin(), mesh1.points().end());
		Kernel::Iso_cuboid_3 bbox0 = CGAL::bounding_box(mesh0.points().begin(), mesh0.points().end());

		auto bbox_p = CGAL::intersection(bbox0, bbox1);
		Kernel::Iso_cuboid_3 bbox = boost::get<Kernel::Iso_cuboid_3>(bbox_p.value());


		for (auto e : mesh0.edges())
		{
			if (!mesh0.is_border(e)) continue;


			auto v0 = mesh0.vertex(e, 0);
			auto v1 = mesh0.vertex(e, 0);

			if (mesh0.is_border(v0) && !bbox.has_on_unbounded_side(mesh0.point(v0))) vd0.push_back(v0);
			if (mesh0.is_border(v1) && !bbox.has_on_unbounded_side(mesh0.point(v1))) vd0.push_back(v1);
		}

		for (auto e : mesh1.edges())
		{
			if (!mesh1.is_border(e)) continue;

			auto v0 = mesh1.vertex(e, 0);
			auto v1 = mesh1.vertex(e, 0);

			if (mesh1.is_border(v0) && !bbox.has_on_unbounded_side(mesh1.point(v0))) vd1.push_back(v0);
			if (mesh1.is_border(v1) && !bbox.has_on_unbounded_side(mesh1.point(v1))) vd1.push_back(v1);
		}

		return 0;
	}
}
